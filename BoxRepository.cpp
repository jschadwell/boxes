#include "BoxRepository.h"
#include <iostream>
#include <utility>

BoxRepository::BoxRepository() {}

BoxRepository::~BoxRepository() {}

bool BoxRepository::init(std::string& xmlFile) {
    if (!loadConfigFile(xmlFile)) {
        return false;
    }

    if (!validateConfig()) {
        return false;
    }


    for (auto&& item : _boxMap) {
        item.second->print();
    }

    return true;
}

bool BoxRepository::loadConfigFile(std::string& xmlFile) {
    // Parse the XML file into a property tree
    try {
        pt::read_xml(xmlFile, _tree);
    } catch (const pt::xml_parser::xml_parser_error& e) {
        errorMsg(e);
        return false;
    }

    return true;
}

bool BoxRepository::validateConfig() {
    try {
        for (const pt::ptree::value_type& v : _tree.get_child("nestconfig")) {
            if (v.first == "box") {
                std::string id = v.second.get<std::string>("<xmlattr>.id");
                if (id == "") {
                    throw pt::ptree_error("Box element with empty ID encountered");
                }

                auto status = _boxMap.insert(std::make_pair(id, std::make_unique<Box>(id)));
                
                if (!status.second) {
                    // Duplicate element found
                    throw pt::ptree_error("Duplicate xml element (" + id + ") found");
                }
            } else {
                throw pt::ptree_error("Invalid xml element (" + v.first + ") found");
            }
        }
    } catch (const std::exception& e) {
        errorMsg(e);
        return false;
    }

    return true;
}

void BoxRepository::errorMsg(const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}