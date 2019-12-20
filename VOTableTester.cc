#include <iostream>

#include "VOTableCarrier.h"
#include "VOTableParser.h"

using namespace carta;

void TestVOTableCarrier1(std::string filename);
void TestVOTableCarrier2(std::string filename);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <VOTable_file>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];

    /*
     * this initialize the library and check potential ABI mismatches
     * between the version it was compiled for and the actual shared
     * library used.
     */
    LIBXML_TEST_VERSION

    TestVOTableCarrier1(filename);
    // TestVOTableCarrier2(filename);

    return 0;
}

void TestVOTableCarrier1(std::string filename) {
    VOTableCarrier* carrier = new VOTableCarrier();

    auto t_start = std::chrono::high_resolution_clock::now();
    VOTableParser parser(filename, carrier);
    auto t_end = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time spending for the parser: " << dt << "(ms)" << std::endl;

    carrier->PrintData();
    delete carrier;
}

void TestVOTableCarrier2(std::string filename) {
    VOTableCarrier carrier = VOTableCarrier();

    auto t_start = std::chrono::high_resolution_clock::now();
    VOTableParser parser(filename, &carrier);
    auto t_end = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time spending for the parser: " << dt << "(ms)" << std::endl;

    carrier.PrintData();
}