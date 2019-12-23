#include "Catalog.h"

#include <dirent.h>
#include <stdio.h> /* defines the FILENAME_MAX */
#include <sys/stat.h>
#include <unistd.h> // Defines the function getcwd(...)

#include "VOTableCarrier.h"
#include "VOTableParser.h"

using namespace carta::catalog;

void Controller::OnFileListRequest(FileListRequest file_list_request, FileListResponse& file_list_response) {
    bool success(false);
    std::string message;
    std::string directory(file_list_request.directory);

    // Replace the $BASE with current working path
    std::string base_path("$BASE");
    if (directory.find(base_path) != std::string::npos) {
        std::string current_working_path = GetCurrentWorkingPath();
        directory.replace(directory.find(base_path), base_path.length(), current_working_path);
    }

    // Get a list of files under the directory
    DIR* current_path;
    struct dirent* current_entry;
    if ((current_path = opendir(directory.c_str()))) {
        success = true; // The directory exists
        while ((current_entry = readdir(current_path))) {
            if (strcmp(current_entry->d_name, ".") != 0 && strcmp(current_entry->d_name, "..") != 0) {
                std::string tmp_name = current_entry->d_name;
                // Check is it a XML file
                if (tmp_name.substr(tmp_name.find_last_of(".") + 1) == "xml") {
                    // Check is it a VOTable XML file
                    std::string tmp_path_name = directory + "/" + tmp_name;
                    if (VOTableParser::IsVOTable(tmp_path_name)) {
                        // Get the file size
                        struct stat file_status;
                        stat(tmp_path_name.c_str(), &file_status);
                        std::string tmp_file_description = std::to_string(file_status.st_size) + " (bytes)";
                        // Fill the file info
                        FileInfo tmp_file_info;
                        tmp_file_info.filename = tmp_name;
                        tmp_file_info.file_type = catalog::VOTable;
                        tmp_file_info.description = tmp_file_description;
                        file_list_response.files.push_back(tmp_file_info);
                    }
                } else {
                    // Check is it a sub-directory
                    DIR* sub_path;
                    std::string sub_directory = directory + "/" + current_entry->d_name;
                    if ((sub_path = opendir(sub_directory.c_str()))) {
                        file_list_response.subdirectories.push_back(sub_directory);
                    }
                    closedir(sub_path);
                }
            }
        }
        closedir(current_path);
    } else {
        message = "Can not open the directory: " + directory;
    }

    // Get the directory parent
    std::string parent_directory;
    if (directory.find("/") != std::string::npos) {
        parent_directory = directory.substr(0, directory.find_last_of("/"));
    }

    // Fill the file list response
    file_list_response.success = success;
    file_list_response.message = message;
    file_list_response.directory = directory;
    file_list_response.parent = parent_directory;
}

std::string Controller::GetCurrentWorkingPath() {
    char buff[FILENAME_MAX];
    getcwd(buff, FILENAME_MAX);
    std::string current_working_path(buff);
    return current_working_path;
}