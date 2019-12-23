#include <iostream>

#include "Catalog.h"
#include "VOTableCarrier.h"
#include "VOTableParser.h"

using namespace carta;

void TestControllerOnFileListRequest(std::string directory);

int main(int argc, char* argv[]) {
    TestControllerOnFileListRequest("$BASE/images");
    TestControllerOnFileListRequest("images");
    return 0;
}

void TestControllerOnFileListRequest(std::string directory) {
    catalog::Controller controller = catalog::Controller();
    catalog::FileListRequest file_list_request;
    file_list_request.directory = directory;
    catalog::FileListResponse file_list_response;
    controller.OnFileListRequest(file_list_request, file_list_response);
    file_list_request.Print();
    file_list_response.Print();
}