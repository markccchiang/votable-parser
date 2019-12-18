#include "VOTableCarrier.h"

using namespace carta;

void VOTableCarrier::SetFileName(std::string filename) {
    _filename = filename;
}

void VOTableCarrier::FillFieldAttributes(int count, std::string name, std::string value) {
    if (name == "name") {
        _fields[count].name = value;
    } else if (name == "ID") {
        _fields[count].id = value;
    } else if (name == "datatype") {
        _fields[count].datatype = value;
    } else if (name == "arraysize") {
        _fields[count].arraysize = value;
    } else if (name == "width") {
        _fields[count].width = value;
    } else if (name == "precision") {
        _fields[count].precision = value;
    } else if (name == "xtype") {
        _fields[count].xtype = value;
    } else if (name == "unit") {
        _fields[count].unit = value;
    } else if (name == "ucd") {
        _fields[count].ucd = value;
    } else if (name == "utype") {
        _fields[count].utype = value;
    } else if (name == "ref") {
        _fields[count].ref = value;
    } else if (name == "type") {
        _fields[count].type = value;
    } else {
        std::cerr << "Can not recognize the FIELD attribute!" << std::endl;
    }
}

void VOTableCarrier::FillFieldDescriptions(int count, std::string value) {
    _fields[count].description = value;
}

void VOTableCarrier::FillTrValues(int count, std::string value) {
    _trs[count].push_back(value);
}

void VOTableCarrier::PrintData() {
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "File Name: " << _filename << std::endl;
    std::cout << "------------------------------------------------------------------\n";
    for (std::pair<int, Field> field : _fields) {
        std::cout << "Field(" << field.first << "): " << std::endl;
        field.second.Print();
        std::cout << "------------------------------------------------------------------\n";
    }
    for (std::pair<int, std::vector<std::string>> tr : _trs) {
        auto& values = tr.second;
        std::cout << "Tr(" << tr.first << "): row size = " << values.size() << std::endl;
        std::cout << "    | ";
        for (int i = 0; i < values.size(); ++i) {
            std::cout << values[i] << " | ";
        }
        std::cout << "\n------------------------------------------------------------------\n";
    }
}