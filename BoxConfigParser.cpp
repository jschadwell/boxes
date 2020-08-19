#include "BoxConfigParser.h"
#include <set>
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <map>
#include <string>
#include <utility>

const char BOXES_ARRAY[] = "boxes";
const char BOX_ITEM[] = "box";
const char CHILDREN_ITEM[] = "children";

BoxUPtr BoxConfigParser::parse(char* configFile) {
    try {
        _tomlConfig = toml::parse_file(configFile);
    } catch (const toml::parse_error& err) {
        std::cerr << "Error: " << err << "\n";
        return nullptr;
    }

    if (!_tomlConfig[BOXES_ARRAY]) {
        std::cerr << "Error: Unable to find (" << BOXES_ARRAY << ")" << "\n";
        return nullptr;
    }

    // First pass - parse all of the box names
    if (!parseBoxNames()) {
        return nullptr;
    }

    // Second pass - parse all of the children
    if (!parseBoxChildren()) {
        return nullptr;
    }

    return BoxUPtr(getTopLevelBox());
}

bool BoxConfigParser::parseBoxNames() {
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
        auto pos = _boxMap.find(boxName);
        if (pos != _boxMap.end()) {
            std::cerr << "Error: Duplicate name (" << boxName << ") found" << "\n";
            return false;
        }

        // Store the box
        _boxMap.insert(std::pair<std::string, Box*>(boxName, new Box(boxName)));
    }

    return true;
}

bool BoxConfigParser::parseBoxChildren() {
    toml::array* boxArray = _tomlConfig[BOXES_ARRAY].as_array();
    for (auto boxIter = boxArray->begin(); boxIter != boxArray->end(); boxIter++) {
        toml::table* boxTable = boxIter->as_table();
        auto boxItem = boxTable->find(BOX_ITEM);
        std::string boxName = std::string(*(boxItem->second.as_string()));
        auto childrenItem = boxTable->find(CHILDREN_ITEM);
        if (childrenItem == boxTable->end()) {
            // Box item doesn't have any children, so just continue on to the next box item
            continue;
        }

        auto children = childrenItem->second.as_array();
        for (auto cIter = children->begin(); cIter != children->end(); cIter++) {
            std::string childName = std::string(*(cIter->as_string()));
            auto pos = _boxMap.find(childName);
            if (pos == _boxMap.end()) {
                std::cerr << "Error: Invalid child box (" << childName << ")" << "\n";
                return false;
            }

            if (_boxMap.at(childName) == nullptr) {
                std::cerr << "Duplicate child box (" << childName << ") found" << "\n";
                return false;
            }


            // Add child to the appropriate parent
            _boxMap.at(boxName)->addChild(_boxMap.at(childName));
        }
    }

    return true;
}

Box* BoxConfigParser::getTopLevelBox() {
    std::set<std::string> boxSet;

    // Make a set containing all of the box names. We'll use the set to find the main box
    for (auto&& box : _boxMap) {
        boxSet.insert(box.first);
    }

    // Go through the box map and find all of the boxes that have a parent. The leftover box
    // will be the main box. NOTE: There should only be one box left over.
    for (auto&& box : _boxMap) {
        if (!box.second->hasChildren()) {
            continue;
        }

        for (auto iter = box.second->begin(); iter != box.second->end(); iter++) {
            auto childName = (*iter)->getName();
            boxSet.erase(childName);
        }
    }

    int topLevelBoxCount = 0;
    Box* topLevelBox = nullptr;
    for (auto iter = boxSet.begin(); iter != boxSet.end(); iter++) {
        topLevelBox = _boxMap.at(*iter);
        ++topLevelBoxCount;
    }

    if (topLevelBoxCount > 1) {
        std::cerr << "Error: multiple top level boxes found" << "\n";
        return nullptr;
    }

    return topLevelBox;
}