#include "VOTableParser.h"

using namespace carta;

VOTableParser::VOTableParser(std::string filename, VOTableCarrier* carrier, bool verbose) : _carrier(carrier), _verbose(verbose) {
    _reader = xmlReaderForFile(filename.c_str(), NULL, 0);
    if (_reader == nullptr) {
        std::cerr << "Unable to open " << filename << std::endl;
    }
    _carrier->SetFileName(filename);
    Skim(); // Skim the VOTable
}

VOTableParser::~VOTableParser() {
    xmlFreeTextReader(_reader);

    // Cleanup function for the XML library.
    xmlCleanupParser();

    // This is to debug memory for regression tests
    xmlMemoryDump();
}

void VOTableParser::Skim() {
    int result;
    do {
        result = xmlTextReaderRead(_reader);
        if (result) {
            Parse(); // Parse the VOTable and store data in the VOTableCarrier
        } else {
            if (_verbose) {
                std::cout << "End of the XML file." << std::endl;
            }
            break;
        }
    } while (true);
}

void VOTableParser::Parse() {
    int node_type = xmlTextReaderNodeType(_reader);
    xmlChar* name_xmlchar;
    xmlChar* value_xmlchar;
    name_xmlchar = xmlTextReaderName(_reader);
    value_xmlchar = xmlTextReaderValue(_reader);

    std::string name;
    std::string value;
    name = (char*)name_xmlchar;
    xmlFree(name_xmlchar); // Not sure if it is necessary, just for safety.
    if (value_xmlchar) {
        value = (char*)value_xmlchar;
        xmlFree(value_xmlchar); // Not sure if it is necessary, just for safety.
    }

    switch (node_type) {
        case XML_READER_TYPE_ELEMENT:
            Print("<" + name + ">", value);
            _pre_element_name = _element_name;
            _element_name = GetElementName(name);
            IncreaseElementCounts(_element_name);
            // Loop through the attributes
            while (xmlTextReaderMoveToNextAttribute(_reader)) {
                Parse();
            }
            break;
        case XML_READER_TYPE_END_ELEMENT:
            Print("</" + name + ">", value);
            if (_td_counts) {
                // Fill the TR element values as "" if there is an empty column, i.e. <TD></TD>.
                _carrier->FillTrValues(_tr_counts, "");
                --_td_counts; // Decrease the TD counter in order to mark such TR element has been filled
            }
            break;
        case XML_READER_TYPE_ATTRIBUTE:
            Print("    " + name, value);
            FillElementAttributes(_element_name, name, value);
            break;
        case XML_READER_TYPE_TEXT:
            Print("    " + name, value);
            FillElementValues(_element_name, value);
            break;

            // Regardless the following node types
        case XML_READER_TYPE_NONE:
            break;
        case XML_READER_TYPE_SIGNIFICANT_WHITESPACE:
            break;
        case XML_READER_TYPE_WHITESPACE:
            break;
        case XML_READER_TYPE_CDATA:
            break;
        case XML_READER_TYPE_ENTITY_REFERENCE:
            break;
        case XML_READER_TYPE_ENTITY:
            break;
        case XML_READER_TYPE_PROCESSING_INSTRUCTION:
            break;
        case XML_READER_TYPE_COMMENT:
            break;
        case XML_READER_TYPE_DOCUMENT:
            break;
        case XML_READER_TYPE_DOCUMENT_TYPE:
            break;
        case XML_READER_TYPE_DOCUMENT_FRAGMENT:
            break;
        case XML_READER_TYPE_NOTATION:
            break;

        default:
            std::cerr << "Fail to parse the XML text!" << std::endl;
    }
}

void VOTableParser::Print(std::string name, std::string value) {
    if (_verbose) {
        if (name == "" && value != "") {
            std::cout << value << std::endl;
        } else if (name != "" && value == "") {
            std::cout << name << std::endl;
        } else {
            std::cout << name << " : " << value << std::endl;
        }
    }
}

VOTableParser::ElementName VOTableParser::GetElementName(std::string name) {
    if (strcmp(name.c_str(), "VOTABLE") == 0) {
        return VOTABLE;
    } else if (strcmp(name.c_str(), "RESOURCE") == 0) {
        return RESOURCE;
    } else if (strcmp(name.c_str(), "DESCRIPTION") == 0) {
        return DESCRIPTION;
    } else if (strcmp(name.c_str(), "DEFINITIONS") == 0) {
        return DEFINITIONS;
    } else if (strcmp(name.c_str(), "INFO") == 0) {
        return INFO;
    } else if (strcmp(name.c_str(), "PARAM") == 0) {
        return PARAM;
    } else if (strcmp(name.c_str(), "TABLE") == 0) {
        return TABLE;
    } else if (strcmp(name.c_str(), "FIELD") == 0) {
        return FIELD;
    } else if (strcmp(name.c_str(), "GROUP") == 0) {
        return GROUP;
    } else if (strcmp(name.c_str(), "FIELDref") == 0) {
        return FIELDref;
    } else if (strcmp(name.c_str(), "PARAMref") == 0) {
        return PARAMref;
    } else if (strcmp(name.c_str(), "VALUES") == 0) {
        return VALUES;
    } else if (strcmp(name.c_str(), "MIN") == 0) {
        return MIN;
    } else if (strcmp(name.c_str(), "MAX") == 0) {
        return MAX;
    } else if (strcmp(name.c_str(), "OPTION") == 0) {
        return OPTION;
    } else if (strcmp(name.c_str(), "LINK") == 0) {
        return LINK;
    } else if (strcmp(name.c_str(), "DATA") == 0) {
        return DATA;
    } else if (strcmp(name.c_str(), "TABLEDATA") == 0) {
        return TABLEDATA;
    } else if (strcmp(name.c_str(), "TD") == 0) {
        return TD;
    } else if (strcmp(name.c_str(), "TR") == 0) {
        return TR;
    } else if (strcmp(name.c_str(), "FITS") == 0) {
        return FITS;
    } else if (strcmp(name.c_str(), "BINARY") == 0) {
        return BINARY;
    } else if (strcmp(name.c_str(), "STREAM") == 0) {
        return STREAM;
    } else if (strcmp(name.c_str(), "COOSYS") == 0) {
        return COOSYS;
    } else {
        return NONE;
    }
}

void VOTableParser::IncreaseElementCounts(ElementName element_name) {
    switch (element_name) {
        case COOSYS:
            ++_coosys_counts;
        case FIELD:
            ++_field_counts;
            break;
        case TR:
            ++_tr_counts;
            break;
        case TD:
            ++_td_counts;
        default:; // Do not count any elements
    }
}

void VOTableParser::FillElementAttributes(ElementName element_name, std::string name, std::string value) {
    switch (element_name) {
        case COOSYS:
            _carrier->FillCoosysAttributes(_coosys_counts, name, value);
            break;
        case FIELD:
            _carrier->FillFieldAttributes(_field_counts, name, value);
            break;
        default:; // Do not fill any attributes
    }
}

void VOTableParser::FillElementValues(ElementName element_name, std::string value) {
    switch (element_name) {
        case DESCRIPTION:
            if (_pre_element_name == FIELD) {
                _carrier->FillFieldDescriptions(_field_counts, value);
            }
            break;
        case TD:
            if (_td_counts) {
                _carrier->FillTrValues(_tr_counts, value);
                --_td_counts; // Decrease the TD counter in order to mark such TR element has been filled
            }
            break;
        default:; // Do not fill any values
    }
}