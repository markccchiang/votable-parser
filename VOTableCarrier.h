#ifndef CARTA_BACKEND__VOTABLECARRIER_H_
#define CARTA_BACKEND__VOTABLECARRIER_H_

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

namespace carta {

class VOTableCarrier {
    // For the element <COOSYS> and its attributes
    struct Coosys {
        std::string id;
        std::string equinox;
        std::string epoch;
        std::string system;
        void Print() {
            std::cout << "    id      = " << id << std::endl;
            std::cout << "    equinox = " << equinox << std::endl;
            std::cout << "    epoch   = " << epoch << std::endl;
            std::cout << "    system  = " << system << std::endl;
        }
    };

    // For the element <FIELD> and its attributes
    struct Field {
        std::string name;
        std::string id;
        std::string datatype;
        std::string arraysize;
        std::string width;
        std::string precision;
        std::string xtype;
        std::string unit;
        std::string ucd;
        std::string utype;
        std::string ref;
        std::string type;
        std::string description;
        void Print() {
            std::cout << "    name        = " << name << std::endl;
            std::cout << "    id          = " << id << std::endl;
            std::cout << "    datatype    = " << datatype << std::endl;
            std::cout << "    arraysize   = " << arraysize << std::endl;
            std::cout << "    width       = " << width << std::endl;
            std::cout << "    precision   = " << precision << std::endl;
            std::cout << "    xtype       = " << xtype << std::endl;
            std::cout << "    unit        = " << unit << std::endl;
            std::cout << "    ucd         = " << ucd << std::endl;
            std::cout << "    utype       = " << utype << std::endl;
            std::cout << "    ref         = " << ref << std::endl;
            std::cout << "    type        = " << type << std::endl;
            std::cout << "    description = " << description << std::endl;
        }
    };

    // For the element <PARAM> with its attributes
    struct Param : Field {
        std::string value;
    };

public:
    VOTableCarrier(){};
    ~VOTableCarrier(){};

    void SetFileName(std::string filename);
    void SetVOTableVersion(std::string version);
    void FillCoosysAttributes(int count, std::string name, std::string value);
    void FillFieldAttributes(int count, std::string name, std::string value);
    void FillFieldDescriptions(int count, std::string value);
    void FillTrValues(int count, std::string value);

    void PrintData();

private:
    std::string _filename;
    std::string _votable_version = "";                      // VOTable version, "" means this is not the VOTable XML file.
    std::unordered_map<int, Coosys> _coosys;                // unordered map for the element <COOSYS>: <COOSYS count, COOSYS attributes>
    std::unordered_map<int, Field> _fields;                 // unordered map for the element <FIELD>: <FIELD count, FIELD attributes>
    std::unordered_map<int, std::vector<std::string>> _trs; // unordered map for the element <TR>: <TR count, row data>
};

} // namespace carta

#endif // CARTA_BACKEND__VOTABLECARRIER_H_