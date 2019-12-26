#include <iostream>

#include "VOTableCarrier.h"
#include "VOTableParser.h"

using namespace catalog;

void TestScanAllVOTable1(std::string filename);
void TestScanAllVOTable2(std::string filename);
void TestScanVOTableHeaders1(std::string filename);
void TestScanVOTableHeaders2(std::string filename);
void TestIsVOTable(std::string filename);

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

    // TestScanAllVOTable1(filename);
    // TestScanAllVOTable2(filename);
    TestScanVOTableHeaders1(filename);
    // TestScanVOTableHeaders2(filename);
    // TestIsVOTable(filename);

    return 0;
}

void TestScanAllVOTable1(std::string filename) {
    VOTableCarrier* carrier = new VOTableCarrier();

    auto t_start = std::chrono::high_resolution_clock::now();
    VOTableParser parser(filename, carrier);
    auto t_end = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time spending for the parser: " << dt << "(ms)" << std::endl;

    carrier->PrintData();
    delete carrier;
}

void TestScanAllVOTable2(std::string filename) {
    VOTableCarrier carrier = VOTableCarrier();

    auto t_start = std::chrono::high_resolution_clock::now();
    VOTableParser parser(filename, &carrier);
    auto t_end = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time spending for the parser: " << dt << "(ms)" << std::endl;

    carrier.PrintData();
}

void TestScanVOTableHeaders1(std::string filename) {
    VOTableCarrier* carrier = new VOTableCarrier();

    auto t_start = std::chrono::high_resolution_clock::now();
    VOTableParser parser(filename, carrier, true);
    auto t_end = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time spending for the parser: " << dt << "(ms)" << std::endl;

    carrier->PrintData();
    delete carrier;
}

void TestScanVOTableHeaders2(std::string filename) {
    VOTableCarrier carrier = VOTableCarrier();

    auto t_start = std::chrono::high_resolution_clock::now();
    VOTableParser parser(filename, &carrier, true);
    auto t_end = std::chrono::high_resolution_clock::now();
    auto dt = std::chrono::duration<double, std::milli>(t_end - t_start).count();
    std::cout << "Time spending for the parser: " << dt << "(ms)" << std::endl;

    carrier.PrintData();
}

void TestIsVOTable(std::string filename) {
    if (VOTableParser::IsVOTable(filename)) {
        std::cout << "File: " << filename << " is a VOTable." << std::endl;
    } else {
        std::cout << "File: " << filename << " is NOT a VOTable." << std::endl;
    }
}