#include "BoxConfigParser.h"
#include <set>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <set>
#include <string>
#include <utility>

const char BOXES_ARRAY[] = "boxes";
const char BOX_ITEM[] = "box";
const char CHILDREN_ITEM[] = "children";

bool BoxConfigParser::parse(char* configFile, BoxConfigMap& boxConfig) {
    try {
        _tomlConfig = toml::parse_file(configFile);
    } catch (const toml::parse_error& err) {
        std::cerr << "Error: " << err << "\n";
        return false;
    }

    if (!_tomlConfig[BOXES_ARRAY]) {
        std::cerr << "Error: Unable to find (" << BOXES_ARRAY << ")" << "\n";
        return false;
    }

    // First pass - parse all of the box names
    if (!parseBoxNames(boxConfig)) {
        return false;
    }

    // Second pass - parse all of the children
    if (!parseBoxChildren(boxConfig)) {
        return false;
    }

    return true;
}

bool BoxConfigParser::parseBoxNames(BoxConfigMap& boxConfig) {
    toml::array* boxArray = _tomlConfig[BOXES_ARRAY].as_array();
    for (auto iter = boxArray->begin(); iter != boxArray->end(); iter++) {
        toml::table* boxTable = iter->as_table();
        auto boxItem = boxTable->find(BOX_ITEM);
        if (boxItem == boxTable->end()) {
            std::cerr << "Error: Unable to find (" << BOX_ITEM << ") in " << BOXES_ARRAY << "\n";
            return false;
        }

        // Determine whether this is a duplicate box
        std::string boxName = std::string(*(boxItem->second.as_string()));
        auto pos = boxConfig.find(boxName);
        if (pos != boxConfig.end()) {
            std::cerr << "Error: Duplicate name (" << boxName << ") found" << "\n";
            return false;
        }

        // Store the box name

        boxConfig.insert(std::pair<BoxName, BoxChildrenUPtr>(boxName, std::make_unique<BoxChildren>()));
    }

    return true;
}

bool BoxConfigParser::parseBoxChildren(BoxConfigMap& boxConfig) {
    toml::array* boxArray = _tomlConfig[BOXES_ARRAY].as_array();
    for (auto iter = boxArray->begin(); iter != boxArray->end(); iter++) {
        toml::table* boxTable = iter->as_table();

        auto childrenItem = boxTable->find(CHILDREN_ITEM);
        if (childrenItem == boxTable->end()) {
            // Box item doesn't have any children, so just continue on to the next item
            continue;
        }

        auto children = childrenItem->second.as_array();
        for (auto cIter = children->begin(); cIter != children->end(); cIter++) {
            std::string childName = std::string(*(cIter->as_string()));
            auto pos = boxConfig.find(childName);
            if (pos == boxConfig.end()) {
                std::cerr << "Error: Invalid child box (" << childName << ")" << "\n";
                return false;
            }

            // Store the child
            auto parentItem = boxTable->find(BOX_ITEM);
            std::string parentName = std::string(*(parentItem->second.as_string()));
            boxConfig.at(parentName)->push_back(childName);
        }
    }

    return true;
}