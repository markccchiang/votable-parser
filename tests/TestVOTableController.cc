#include <iostream>

#include "../VOTableController.h"

using namespace catalog;

std::unique_ptr<Controller> _controller;

void TestOnFilterRequest1();
void TestOnFilterRequest2();
void TestOnFilterRequest3();
void TestOnFilterRequest4();
void TestOnFilterRequest(OpenFileRequest open_file_request, FilterRequest filter_request);
void TestOnFilterRequest2(OpenFileRequest open_file_request, FilterRequest filter_request);
void TestOnOpenFileRequest();
void TestOnOpenFileRequest(OpenFileRequest open_file_request);
void TestOnFileListRequest();
void TestOnFileListRequest(FileListRequest file_list_request);
void TestOnFileInfoRequest();
void TestOnFileInfoRequest(FileInfoRequest file_info_request);

void TestMultiFiles();

int main(int argc, char* argv[]) {
    // TestOnFileListRequest();
    // TestOnFileInfoRequest();
    // TestOnOpenFileRequest();
    // TestOnFilterRequest1();
    // TestOnFilterRequest2();
    // TestOnFilterRequest3();
    // TestOnFilterRequest4();
    TestMultiFiles();

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
    filter_request.image_bounds = {-1, -1, -1, -1};

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
    filter_request.image_bounds = {-1, -1, -1, -1};

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
    filter_request.image_bounds = {-1, -1, -1, -1};
    filter_request.hided_table_headers = {"Name", "RVel", "e_RVel", "R"};

    FilterConfig filter_config1;
    filter_config1.column_name = "RA";
    filter_config1.comparison_operator = FromTo;
    filter_config1.min = 0;
    filter_config1.max = 100;
    filter_request.filter_configs.push_back(filter_config1);

    TestOnFilterRequest(open_file_request, filter_request);
}

void TestOnFilterRequest4() {
    OpenFileRequest open_file_request;
    open_file_request.directory = "images";
    open_file_request.filename = "M17_SWex_simbad_2arcmin.xml";
    open_file_request.file_id = 0;
    open_file_request.preview_data_size = 0;

    FilterRequest filter_request;
    filter_request.file_id = 0;
    filter_request.subset_start_index = 0;
    filter_request.subset_data_size = 10;
    filter_request.region_id = 0;
    filter_request.image_bounds = {-1, -1, -1, -1};
    filter_request.hided_table_headers = {"OID4", "XMM:Obsno", "IUE:bibcode", "IUE:F", "IUE:Comments", "IUE:S", "IUE:CEB", "IUE:m",
        "IUE:ExpTim", "IUE:Time", "IUE:ObsDate", "IUE:MD", "IUE:FES", "IUE:A", "IUE:IMAGE"};

    FilterConfig filter_config1;
    filter_config1.column_name = "RA_d";
    filter_config1.comparison_operator = GreaterThan;
    filter_config1.min = 275.089;
    filter_config1.max = 275.089;
    filter_request.filter_configs.push_back(filter_config1);

    // TestOnFilterRequest(open_file_request, filter_request);
    TestOnFilterRequest2(open_file_request, filter_request);
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

void TestOnFilterRequest2(OpenFileRequest open_file_request, FilterRequest filter_request) {
    // Open file
    OpenFileResponse open_file_response;
    _controller = std::unique_ptr<Controller>(new Controller());
    _controller->OnOpenFileRequest(open_file_request, open_file_response);

    // Filter the file data
    _controller->OnFilterRequest(filter_request, [&](FilterResponse filter_response) {
        // Print partial or final results
        filter_request.Print();
        filter_response.Print();
        std::cout << "\n------------------------------------------------------------------\n";
    });

    // Close file
    CloseFileRequest close_file_request;
    close_file_request.file_id = open_file_request.file_id;
    _controller->OnCloseFileRequest(close_file_request);

    // Delete the Controller
    _controller.reset();
}

void TestMultiFiles() {
    // File list request
    TestOnFileListRequest({"$BASE/images"});
    std::cout << "\n------------------------------------------------------------------\n";

    // File info request
    TestOnFileInfoRequest({"$BASE/images", "simple.xml"});
    std::cout << "\n------------------------------------------------------------------\n";
    TestOnFileInfoRequest({"$BASE/images", "M17_SWex_simbad_2arcmin.xml"});
    std::cout << "\n------------------------------------------------------------------\n";

    // First file messages
    OpenFileRequest open_file_request1;
    open_file_request1.directory = "images";
    open_file_request1.filename = "simple.xml";
    open_file_request1.file_id = 0;
    open_file_request1.preview_data_size = 0;

    FilterRequest filter_request1;
    filter_request1.file_id = 0;
    filter_request1.subset_start_index = 0;
    filter_request1.subset_data_size = 50;
    filter_request1.region_id = 0;
    filter_request1.image_bounds = {-1, -1, -1, -1};
    filter_request1.hided_table_headers = {"Name", "RVel", "e_RVel", "R"};

    FilterConfig filter_config1;
    filter_config1.column_name = "RA";
    filter_config1.comparison_operator = FromTo;
    filter_config1.min = 0;
    filter_config1.max = 100;
    filter_config1.data_type = FLOAT; // This variable is not used in the filter function
    filter_request1.filter_configs.push_back(filter_config1);

    // Second file messages
    OpenFileRequest open_file_request2;
    open_file_request2.directory = "images";
    open_file_request2.filename = "M17_SWex_simbad_2arcmin.xml";
    open_file_request2.file_id = 1;
    open_file_request2.preview_data_size = 0;

    FilterRequest filter_request2;
    filter_request2.file_id = 1;
    filter_request2.subset_start_index = 0;
    filter_request2.subset_data_size = 10;
    filter_request2.region_id = 0;
    filter_request2.image_bounds = {-1, -1, -1, -1};
    filter_request2.hided_table_headers = {"OID4", "XMM:Obsno", "IUE:bibcode", "IUE:F", "IUE:Comments", "IUE:S", "IUE:CEB", "IUE:m",
        "IUE:ExpTim", "IUE:Time", "IUE:ObsDate", "IUE:MD", "IUE:FES", "IUE:A", "IUE:IMAGE"};

    FilterConfig filter_config2;
    filter_config2.column_name = "RA_d";
    filter_config2.comparison_operator = GreaterThan;
    filter_config2.min = 275.089;
    filter_config2.max = 275.089;
    filter_config2.data_type = DOUBLE; // This variable is not used in the filter function
    filter_request2.filter_configs.push_back(filter_config2);

    // Create the Controller
    _controller = std::unique_ptr<Controller>(new Controller());

    // Open files
    OpenFileResponse open_file_response1;
    OpenFileResponse open_file_response2;
    _controller->OnOpenFileRequest(open_file_request1, open_file_response1);
    _controller->OnOpenFileRequest(open_file_request2, open_file_response2);

    // Filter the first file
    _controller->OnFilterRequest(filter_request1, [&](FilterResponse filter_response) {
        // Print partial or final results
        filter_request1.Print();
        filter_response.Print();
        std::cout << "\n------------------------------------------------------------------\n";
    });

    // Filter the second file
    _controller->OnFilterRequest(filter_request2, [&](FilterResponse filter_response) {
        // Print partial or final results
        filter_request1.Print();
        filter_response.Print();
        std::cout << "\n------------------------------------------------------------------\n";
    });

    // Close files
    CloseFileRequest close_file_request1;
    close_file_request1.file_id = open_file_request1.file_id;
    _controller->OnCloseFileRequest(close_file_request1);

    CloseFileRequest close_file_request2;
    close_file_request2.file_id = open_file_request2.file_id;
    _controller->OnCloseFileRequest(close_file_request2);
}