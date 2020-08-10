#include "BoxRepository.h"
#include <iostream>
#include <utility>

BoxRepository::BoxRepository() {}

BoxRepository::~BoxRepository() {}

bool BoxRepository::init(std::string& xmlFile) {
    if (!loadConfigFile(xmlFile)) {
        return false;
    }

    if (!readConfig()) {
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
        errorMsg(e.what());
        return false;
    }

    return true;
}

bool BoxRepository::readConfig() {
    const char ROOT_TAG[] = "nestconfig";
    const char BOX_TAG[] = "box";
    const char CHILD_TAG[] = "child";
    const char ATTR_PREFIX[] = "<xmlattr>";
    const char ID_ATTR[] = "id";
    const char EMPTY_TAG[] = "";
    try {
        // Extract all of the data from the XML config file
        for (const pt::ptree::value_type& node : _tree.get_child(ROOT_TAG)) {
            if (node.first != BOX_TAG) {
                throw pt::ptree_error("Invalid xml element (" + node.first + ") found");                
            }

            pt::ptree subTree = node.second;
            std::string boxId;
            for (const pt::ptree::value_type& childNode : subTree.get_child(EMPTY_TAG)) {
                if (childNode.first == ATTR_PREFIX) {
                    boxId = childNode.second.get<std::string>(ID_ATTR);
                    if (boxId == "") {
                        throw pt::ptree_error("Box element with empty ID encountered");
                    }
                    auto status = _boxMap.insert(std::make_pair(boxId, std::make_unique<Box>(boxId)));
                    if (!status.second) {
                        // Duplicate element found
                        throw pt::ptree_error("Duplicate box (" + boxId + ") found");
                    }
                } else if (childNode.first == CHILD_TAG) {
                    std::string childId = childNode.second.get<std::string>(EMPTY_TAG);
                    if (!_boxMap.at(boxId)->addChild(childId)) {
                        throw pt::ptree_error("Invalid child (" + childId + ") in box (" + boxId + ") found");
                    }
                } else {
                    throw pt::ptree_error("Invalid xml element (" + childNode.first + ") found");
                }
            }
        }
    } catch (const std::exception& e) {
        errorMsg(e.what());
        return false;
    }

    return true;
}

bool BoxRepository::validateConfig() {
    // Make sure all children actually exist
    for (auto iter = begin(_boxMap); iter != end(_boxMap); iter++) {
        std::cout << "Key = " << iter->first << std::endl;
        for (auto&& child : iter->second->getChildren()) {
            std::cout << "Child = " << child << ", " << _boxMap.count(child) << std::endl;
            if (_boxMap.count(child) == 0) {
                std::string msg = "Invalid child (" + child + ") found in box (" + iter->first + ")";
                errorMsg(msg.data());
                return false;
            }
        }
    }

    return true;
}

void BoxRepository::errorMsg(const char* msg) {
    std::cerr << "Error: " << msg << std::endl;
}