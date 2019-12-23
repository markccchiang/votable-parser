#include <iostream>

#include "Catalog.h"

using namespace carta;

void TestControllerOnFileListRequest(std::string directory);

int main(int argc, char* argv[]) {
    TestControllerOnFileListRequest("$BASE/images");
    TestControllerOnFileListRequest("images");
    TestControllerOnFileListRequest("$BASE/no_such_dir");
    TestControllerOnFileListRequest("no_such_dir");

    return 0;
}

void TestControllerOnFileListRequest(std::string directory) {
    catalog::FileListRequest file_list_request;
    file_list_request.directory = directory;
    catalog::FileListResponse file_list_response;
    catalog::Controller::OnFileListRequest(file_list_request, file_list_response);
    file_list_request.Print();
    file_list_response.Print();
}