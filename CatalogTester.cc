#include <iostream>

#include "Catalog.h"

using namespace carta;

void TestOnOpenFileRequest();
void TestOnOpenFileRequest(catalog::OpenFileRequest open_file_request);
void TestOnFileListRequest();
void TestOnFileListRequest(catalog::FileListRequest file_list_request);
void TestOnFileInfoRequest();
void TestOnFileInfoRequest(catalog::FileInfoRequest file_info_request);

int main(int argc, char* argv[]) {
    // TestOnFileListRequest();
    // TestOnFileInfoRequest();
    TestOnOpenFileRequest();

    return 0;
}

void TestOnFileListRequest() {
    TestOnFileListRequest({"$BASE/images"});
    TestOnFileListRequest({"images"});
    TestOnFileListRequest({"$BASE/no_such_dir"});
    TestOnFileListRequest({"no_such_dir"});
}

void TestOnFileListRequest(catalog::FileListRequest file_list_request) {
    catalog::FileListResponse file_list_response;
    catalog::Controller::OnFileListRequest(file_list_request, file_list_response);
    file_list_request.Print();
    file_list_response.Print();
}

void TestOnFileInfoRequest() {
    TestOnFileInfoRequest({"images", "simple.xml"});
    TestOnFileInfoRequest({"$BASE/images", "simple.xml"});
    TestOnFileInfoRequest({"images", "M17_SWex_simbad_2arcmin.xml"});
    TestOnFileInfoRequest({"$BASE/images", "M17_SWex_simbad_2arcmin.xml"});
}

void TestOnFileInfoRequest(catalog::FileInfoRequest file_info_request) {
    catalog::FileInfoResponse file_info_response;
    catalog::Controller::OnFileInfoRequest(file_info_request, file_info_response);

    file_info_request.Print();
    file_info_response.Print();
}

void TestOnOpenFileRequest() {
    TestOnOpenFileRequest({"images", "simple.xml", 0, 0});
    TestOnOpenFileRequest({"$BASE/images", "simple.xml", 0, 0});
    TestOnOpenFileRequest({"images", "M17_SWex_simbad_2arcmin.xml", 0, 0});
    TestOnOpenFileRequest({"$BASE/images", "M17_SWex_simbad_2arcmin.xml", 0, 0});
}

void TestOnOpenFileRequest(catalog::OpenFileRequest open_file_request) {
    catalog::OpenFileResponse open_file_response;
    catalog::Controller controller = catalog::Controller();
    controller.OnOpenFileRequest(open_file_request, open_file_response);

    open_file_request.Print();
    open_file_response.Print();
}