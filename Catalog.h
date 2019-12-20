#ifndef CARTA_BACKEND__CATALOG_H_
#define CARTA_BACKEND__CATALOG_H_

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace carta {
namespace catalog {

// Enums
enum FileType { VOTable = 0 };

enum ComparisonOperator {
    EqualTo = 0,
    NotEqualTo = 1,
    LessThan = 2,
    GreaterThan = 3,
    LessThanOrEqualTo = 4,
    GreaterThanOrEqualTo = 5,
    BetweenAnd = 6,
    FromTo = 7
};

enum DataType { BOOL = 0, STRING = 1, INT = 2, LONG = 3, FLOAT = 4, DOUBLE = 5 };

// Structs for sub-message
struct FileInfo {
    std::string filename;
    FileType file_type;
    std::string description;
};

struct Header {
    std::string column_name;
    DataType data_type;
    int column_index;
    int data_type_index;
    std::string description;
    std::string unit;
};

struct ColumnsData {
    std::vector<std::vector<bool>> bool_columns;
    std::vector<std::vector<std::string>> string_columns;
    std::vector<std::vector<int>> int_columns;
    std::vector<std::vector<long>> long_columns;
    std::vector<std::vector<float>> float_columns;
    std::vector<std::vector<double>> double_columns;
};

struct FilterConfig {
    std::string column_name;
    ComparisonOperator comparison_operator;
    float min;
    float max;
    std::string sub_string;
    DataType data_type;
};

struct ImageBounds {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
};

// Structs for request messages
struct OpenFile {
    std::string directory;
    std::string filename;
    int file_id;
    int preview_data_size;
};

struct CloseFile {
    int file_id;
};

struct FileListRequest {
    std::string directory;
};

struct FileInfoRequest {
    std::string directory;
    std::string filename;
};

struct FilterRequest {
    std::vector<std::string> hided_table_headers;
    std::vector<FilterConfig> filter_configs;
    int subset_data_size;
    int subset_start_index;
    ImageBounds image_bounds;
    int region_id;
};

// Structs for response messages
struct OpenFileResponse {
    bool success;
    std::string message;
    int file_id;
    FileInfo file_info;
    int data_size;
    std::vector<Header> headers;
    ColumnsData columns_data;
};

struct FileListResponse {
    bool success;
    std::string message;
    std::string directory;
    std::string parent;
    std::vector<FileInfo> files;
    std::vector<std::string> subdirectories;
};

struct FileInfoResponse {
    bool success;
    std::string message;
    FileInfo file_info;
    int data_size;
    std::vector<Header> headers;
};

struct FilterResponse {
    int file_id;
    int region_id;
    std::vector<Header> headers;
    ColumnsData columns_data;
    float progress;
};

} // namespace catalog
} // namespace carta

#endif // CARTA_BACKEND__CATALOG_H_