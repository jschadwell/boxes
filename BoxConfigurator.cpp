#include "BoxConfigurator.h"
#include <iostream>
#include <utility>
#include <algorithm>

// Compares a box configuration item's ID to a given box ID to check for equality.
// returns true if the IDs match, false otherwise.
bool isBoxEqual(std::unique_ptr<BoxConfiguration>& boxConfig, std::string id) {
    return id == boxConfig->getId();
}

BoxConfigurator::BoxConfigurator() {}

BoxConfigurator::~BoxConfigurator() {}

bool BoxConfigurator::loadConfig(std::string& xmlFile, BoxConfigList& configList) {
    if (!readConfigFile(xmlFile)) {
        return false;
    }

    if (!parseConfig(configList)) {
        return false;
    }

    if (!validateConfig(configList)) {
        return false;
    }

    for (auto&& item : configList) {
        item->print();
    }

    return true;
}

bool BoxConfigurator::readConfigFile(std::string& xmlFile) {
    // Parse the XML file into a property tree
    try {
        pt::read_xml(xmlFile, _tree);
    } catch (const pt::xml_parser::xml_parser_error& e) {
        errorMsg(e.what());
        return false;
    }

    return true;
}

bool BoxConfigurator::parseConfig(BoxConfigList& configList) {
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

                    // See if the box is already in the list
                    auto pos = std::find_if(begin(configList), end(configList), std::bind(isBoxEqual, std::placeholders::_1, boxId));
                    if (pos != end(configList)) {
                        // Duplicate element found
                        throw pt::ptree_error("Duplicate box (" + boxId + ") found");
                    }

                    // Add thew new configuration item to the list
                    configList.push_back(std::make_unique<BoxConfiguration>(boxId));

                } else if (childNode.first == CHILD_TAG) {
                    std::string childId = childNode.second.get<std::string>(EMPTY_TAG);
                    auto pos = std::find_if(begin(configList), end(configList), std::bind(isBoxEqual, std::placeholders::_1, boxId));
                    if (!(*pos)->addChild(childId)) {
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

bool BoxConfigurator::validateConfig(BoxConfigList& configList) {
    // Make sure all children actually exist
    for (auto iter = begin(configList); iter != end(configList); iter++) {
        std::cout << "Key = " << (*iter)->getId() << std::endl;
        for (auto&& child : (*iter)->getChildren()) {
            if (std::count_if(begin(configList), end(configList), std::bind(isBoxEqual, std::placeholders::_1, child)) == 0) {
                std::string msg = "Invalid child (" + child + ") found in box (" + (*iter)->getId() + ")";
                errorMsg(msg.data());
                return false;
            }
        }
    }

    return true;
}

void BoxConfigurator::errorMsg(const char* msg) {
    std::cerr << "Error: " << msg << std::endl;
}