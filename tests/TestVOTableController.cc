#include <iostream>

#include "../VOTableController.h"

using namespace catalog;

void TestOnFilterRequest1();
void TestOnFilterRequest2();
void TestOnFilterRequest3();
void TestOnFilterRequest(OpenFileRequest open_file_request, FilterRequest filter_request);
void TestOnOpenFileRequest();
void TestOnOpenFileRequest(OpenFileRequest open_file_request);
void TestOnFileListRequest();
void TestOnFileListRequest(FileListRequest file_list_request);
void TestOnFileInfoRequest();
void TestOnFileInfoRequest(FileInfoRequest file_info_request);

int main(int argc, char* argv[]) {
    // TestOnFileListRequest();
    // TestOnFileInfoRequest();
    // TestOnOpenFileRequest();
    // TestOnFilterRequest1();
    // TestOnFilterRequest2();
    TestOnFilterRequest3();

    return 0;
}

void TestOnFileListRequest() {
    TestOnFileListRequest({"$BASE/images"});
    TestOnFileListRequest({"images"});
    TestOnFileListRequest({"$BASE/no_such_dir"});
    TestOnFileListRequest({"no_such_dir"});
}

void TestOnFileListRequest(FileListRequest file_list_request) {
    FileListResponse file_list_response;
    Controller::OnFileListRequest(file_list_request, file_list_response);
    file_list_request.Print();
    file_list_response.Print();
}

void TestOnFileInfoRequest() {
    TestOnFileInfoRequest({"images", "simple.xml"});
    TestOnFileInfoRequest({"$BASE/images", "simple.xml"});
    TestOnFileInfoRequest({"images", "M17_SWex_simbad_2arcmin.xml"});
    TestOnFileInfoRequest({"$BASE/images", "M17_SWex_simbad_2arcmin.xml"});
}

void TestOnFileInfoRequest(FileInfoRequest file_info_request) {
    FileInfoResponse file_info_response;
    Controller::OnFileInfoRequest(file_info_request, file_info_response);

    file_info_request.Print();
    file_info_response.Print();
}

void TestOnOpenFileRequest() {
    TestOnOpenFileRequest({"images", "simple.xml", 0, 0});
    TestOnOpenFileRequest({"$BASE/images", "simple.xml", 0, 0});
    TestOnOpenFileRequest({"images", "M17_SWex_simbad_2arcmin.xml", 0, 0});
    TestOnOpenFileRequest({"$BASE/images", "M17_SWex_simbad_2arcmin.xml", 0, 0});
}

void TestOnOpenFileRequest(OpenFileRequest open_file_request) {
    // Open file
    OpenFileResponse open_file_response;
    Controller controller = Controller();
    controller.OnOpenFileRequest(open_file_request, open_file_response);

    // Print results
    open_file_request.Print();
    open_file_response.Print();

    // Close file
    CloseFileRequest close_file_request;
    close_file_request.file_id = open_file_request.file_id;
    controller.OnCloseFileRequest(close_file_request);
}

void TestOnFilterRequest1() {
    OpenFileRequest open_file_request;
    open_file_request.directory = "images";
    open_file_request.filename = "simple.xml";
    open_file_request.file_id = 0;
    open_file_request.preview_data_size = 0;

    FilterRequest filter_request;
    filter_request.file_id = 0;
    filter_request.subset_start_index = 0;
    filter_request.subset_data_size = 50;
    filter_request.region_id = 0;
    filter_request.image_bounds.x_min = -1;
    filter_request.image_bounds.x_max = -1;
    filter_request.image_bounds.y_min = -1;
    filter_request.image_bounds.y_max = -1;

    TestOnFilterRequest(open_file_request, filter_request);
}

void TestOnFilterRequest2() {
    OpenFileRequest open_file_request;
    open_file_request.directory = "images";
    open_file_request.filename = "M17_SWex_simbad_2arcmin.xml";
    open_file_request.file_id = 0;
    open_file_request.preview_data_size = 0;

    FilterRequest filter_request;
    filter_request.file_id = 0;
    filter_request.subset_start_index = 0;
    filter_request.subset_data_size = 50;
    filter_request.region_id = 0;
    filter_request.image_bounds.x_min = -1;
    filter_request.image_bounds.x_max = -1;
    filter_request.image_bounds.y_min = -1;
    filter_request.image_bounds.y_max = -1;

    TestOnFilterRequest(open_file_request, filter_request);
}

void TestOnFilterRequest3() {
    OpenFileRequest open_file_request;
    open_file_request.directory = "images";
    open_file_request.filename = "simple.xml";
    open_file_request.file_id = 0;
    open_file_request.preview_data_size = 0;

    FilterRequest filter_request;
    filter_request.file_id = 0;
    filter_request.subset_start_index = 0;
    filter_request.subset_data_size = 50;
    filter_request.region_id = 0;
    filter_request.image_bounds.x_min = -1;
    filter_request.image_bounds.x_max = -1;
    filter_request.image_bounds.y_min = -1;
    filter_request.image_bounds.y_max = -1;
    filter_request.hided_table_headers.push_back("Name");
    filter_request.hided_table_headers.push_back("RVel");
    filter_request.hided_table_headers.push_back("e_RVel");
    filter_request.hided_table_headers.push_back("R");

    FilterConfig filter_config1;
    filter_config1.column_name = "RA";
    filter_config1.comparison_operator = FromTo;
    filter_config1.min = 0;
    filter_config1.max = 100;
    filter_request.filter_configs.push_back(filter_config1);

    TestOnFilterRequest(open_file_request, filter_request);
}

void TestOnFilterRequest(OpenFileRequest open_file_request, FilterRequest filter_request) {
    // Open file
    OpenFileResponse open_file_response;
    Controller controller = Controller();
    controller.OnOpenFileRequest(open_file_request, open_file_response);

    // Filter the file data
    controller.OnFilterRequest(filter_request, [&](FilterResponse filter_response) {
        // Print partial or final results
        filter_request.Print();
        filter_response.Print();
        std::cout << "\n------------------------------------------------------------------\n";
    });

    // Close file
    CloseFileRequest close_file_request;
    close_file_request.file_id = open_file_request.file_id;
    controller.OnCloseFileRequest(close_file_request);
}