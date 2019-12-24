#include "VOTableCarrier.h"

using namespace carta;

void VOTableCarrier::SetFileName(std::string file_path_name) {
    std::size_t found = file_path_name.find_last_of("/");
    _filename = file_path_name.substr(found + 1);
    _directory = file_path_name.substr(0, found);
}

void VOTableCarrier::FillVOTableAttributes(std::string name, std::string version) {
    if (name == "version") {
        _votable_version = version;
    }
}

void VOTableCarrier::FillCoosysAttributes(int count, std::string name, std::string value) {
    if (name == "ID") {
        _coosys[count].id = value;
    } else if (name == "equinox") {
        _coosys[count].equinox = value;
    } else if (name == "epoch") {
        _coosys[count].epoch = value;
    } else if (name == "system") {
        _coosys[count].system = value;
    } else {
        std::cerr << "Can not recognize the COOSYS attribute: " << name << " : " << value << std::endl;
    }
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
        std::cerr << "Can not recognize the FIELD attribute: " << name << " : " << value << std::endl;
    }
}

void VOTableCarrier::FillFieldDescriptions(int count, std::string value) {
    _fields[count].description = value;
}

void VOTableCarrier::FillTdValues(int column_index, std::string value) {
    if (_fields[column_index].datatype == "boolean") {
        // Convert the string to lowercase
        std::transform(value.begin(), value.end(), value.begin(), ::tolower);
        _bool_vectors[column_index].push_back(value == "true");
    } else if (_fields[column_index].datatype == "char") {
        _string_vectors[column_index].push_back(value);
    } else if ((_fields[column_index].datatype == "short") || (_fields[column_index].datatype == "int")) {
        // PS: C++ has no function to convert the "string" to "short", so we just convert it to "int"
        try {
            _int_vectors[column_index].push_back(std::stoi(value));
        } catch (...) {
            _int_vectors[column_index].push_back(std::numeric_limits<int>::quiet_NaN());
        }
    } else if (_fields[column_index].datatype == "long") {
        try {
            _long_vectors[column_index].push_back(std::stol(value));
        } catch (...) {
            _long_vectors[column_index].push_back(std::numeric_limits<long>::quiet_NaN());
        }
    } else if (_fields[column_index].datatype == "float") {
        try {
            _float_vectors[column_index].push_back(std::stof(value));
        } catch (...) {
            _float_vectors[column_index].push_back(std::numeric_limits<float>::quiet_NaN());
        }
    } else if (_fields[column_index].datatype == "double") {
        try {
            _double_vectors[column_index].push_back(std::stod(value));
        } catch (...) {
            _double_vectors[column_index].push_back(std::numeric_limits<double>::quiet_NaN());
        }
    } else {
        // Do not cache the table column if its data type is not in our list
    }
}

void VOTableCarrier::UpdateNumOfTableRows() {
    if (_fields.empty()) {
        std::cerr << "There is no table column!" << std::endl;
        return;
    }
    for (int i = 1; i <= _fields.size(); ++i) {
        if (_bool_vectors.find(i) != _bool_vectors.end()) {
            if (i == 1) {
                _num_of_rows = _bool_vectors[i].size();
            } else if (_num_of_rows != _bool_vectors[i].size()) {
                std::cerr << "The columns sizes are not consistent!" << std::endl;
            }
        } else if (_string_vectors.find(i) != _string_vectors.end()) {
            if (i == 1) {
                _num_of_rows = _string_vectors[i].size();
            } else if (_num_of_rows != _string_vectors[i].size()) {
                std::cerr << "The columns sizes are not consistent!" << std::endl;
            }
        } else if (_int_vectors.find(i) != _int_vectors.end()) {
            if (i == 1) {
                _num_of_rows = _int_vectors[i].size();
            } else if (_num_of_rows != _int_vectors[i].size()) {
                std::cerr << "The columns sizes are not consistent!" << std::endl;
            }
        } else if (_long_vectors.find(i) != _long_vectors.end()) {
            if (i == 1) {
                _num_of_rows = _long_vectors[i].size();
            } else if (_num_of_rows != _long_vectors[i].size()) {
                std::cerr << "The columns sizes are not consistent!" << std::endl;
            }
        } else if (_float_vectors.find(i) != _float_vectors.end()) {
            if (i == 1) {
                _num_of_rows = _float_vectors[i].size();
            } else if (_num_of_rows != _float_vectors[i].size()) {
                std::cerr << "The columns sizes are not consistent!" << std::endl;
            }
        } else if (_double_vectors.find(i) != _double_vectors.end()) {
            if (i == 1) {
                _num_of_rows = _double_vectors[i].size();
            } else if (_num_of_rows != _double_vectors[i].size()) {
                std::cerr << "The columns sizes are not consistent!" << std::endl;
            }
        }
    }
}

void VOTableCarrier::GetTableHeaders(catalog::FileInfoResponse& file_info_response) {
    for (std::pair<int, Field> field : _fields) {
        Field& tmp_field = field.second;
        catalog::Header tmp_header;
        tmp_header.column_name = tmp_field.name;
        tmp_header.data_type = GetDataType(tmp_field.datatype);
        tmp_header.column_index = field.first; // The FIELD index in the VOTable
        tmp_header.data_type_index = -1;       // -1 means there is no corresponding data vector in the catalog::ColumnsData
        tmp_header.description = tmp_field.description;
        tmp_header.unit = tmp_field.unit;
        file_info_response.headers.push_back(tmp_header);
    }
}

void VOTableCarrier::GetTableRowNumber(catalog::FileInfoResponse& file_info_response) {
    UpdateNumOfTableRows();
    file_info_response.data_size = _num_of_rows;
}

catalog::DataType VOTableCarrier::GetDataType(std::string data_type) {
    catalog::DataType catalog_data_type;
    if (data_type == "boolean") {
        catalog_data_type = catalog::BOOL;
    } else if (data_type == "char") {
        catalog_data_type = catalog::STRING;
    } else if (data_type == "short" || data_type == "int") {
        catalog_data_type = catalog::INT;
    } else if (data_type == "long") {
        catalog_data_type = catalog::LONG;
    } else if (data_type == "float") {
        catalog_data_type = catalog::FLOAT;
    } else if (data_type == "double") {
        catalog_data_type = catalog::DOUBLE;
    } else {
        catalog_data_type = catalog::NONE;
    }
    return catalog_data_type;
}

void VOTableCarrier::PrintTableElement(int row, int column) {
    if (_bool_vectors.find(column) != _bool_vectors.end()) {
        std::cout << _bool_vectors[column][row] << " | ";
    } else if (_string_vectors.find(column) != _string_vectors.end()) {
        std::cout << _string_vectors[column][row] << " | ";
    } else if (_int_vectors.find(column) != _int_vectors.end()) {
        std::cout << _int_vectors[column][row] << " | ";
    } else if (_long_vectors.find(column) != _long_vectors.end()) {
        std::cout << _long_vectors[column][row] << " | ";
    } else if (_float_vectors.find(column) != _float_vectors.end()) {
        std::cout << _float_vectors[column][row] << " | ";
    } else if (_double_vectors.find(column) != _double_vectors.end()) {
        std::cout << _double_vectors[column][row] << " | ";
    } else {
        std::cout << " | ";
    }
}

void VOTableCarrier::PrintData() {
    UpdateNumOfTableRows();
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "File Name           : " << _filename << std::endl;
    std::cout << "File Directory      : " << _directory << std::endl;
    std::cout << "VOTable Version     : " << _votable_version << std::endl;
    std::cout << "Table column size   : " << _fields.size() << std::endl;
    std::cout << "Table row size      : " << _num_of_rows << std::endl;
    std::cout << "------------------------------------------------------------------\n";
    std::cout << "# of bool columns   : " << _bool_vectors.size() << std::endl;
    std::cout << "# of string columns : " << _string_vectors.size() << std::endl;
    std::cout << "# of int columns    : " << _int_vectors.size() << std::endl;
    std::cout << "# of long columns   : " << _long_vectors.size() << std::endl;
    std::cout << "# of float columns  : " << _float_vectors.size() << std::endl;
    std::cout << "# of double columns : " << _double_vectors.size() << std::endl;
    std::cout << "------------------------------------------------------------------\n";
    // Print coordinate systems
    for (std::pair<int, Coosys> coosys : _coosys) {
        std::cout << "Coosys(" << coosys.first << "): " << std::endl;
        coosys.second.Print();
        std::cout << "------------------------------------------------------------------\n";
    }
    // Print table fields (column definitions)
    for (std::pair<int, Field> field : _fields) {
        std::cout << "Field(" << field.first << "): " << std::endl;
        field.second.Print();
        std::cout << "------------------------------------------------------------------\n";
    }
    // Print table rows
    for (int i = 0; i < _num_of_rows; ++i) {
        std::cout << "row " << i << ": | ";
        for (int j = 1; j <= _fields.size(); ++j) {
            PrintTableElement(i, j);
        }
        std::cout << "\n------------------------------------------------------------------\n";
    }
}