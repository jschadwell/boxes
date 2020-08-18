#include "BoxConfigParser.h"
#include <set>
#include <iostream>
#include <fstream>
#include <cstring>

const char BOXES_ARRAY[] = "boxes";
const char BOX_ITEM[] = "box";
const char CHILDREN_ITEM[] = "children";

BoxConfiguration* BoxConfigParser::parse(char* configFile) {
    try {
        _tomlConfig = toml::parse_file(configFile);
    } catch (const toml::parse_error& err) {
        std::cerr << "Error: " << err << "\n";
        return nullptr;
    }

    auto boxes = _tomlConfig[BOXES_ARRAY];
    if (!boxes) {
        std::cerr << "Error: Unable to find (" << BOXES_ARRAY << ")" << "\n";
        return nullptr;
    }

    toml::array* boxArray = boxes.as_array();
    for (auto iter = boxArray->begin(); iter != boxArray->end(); iter++) {
        toml::table* boxTable = iter->as_table();
        auto boxItem = boxTable->find(BOX_ITEM);
        if (boxItem == boxTable->end()) {
            std::cerr << "Error: Unable to find (" << BOX_ITEM << ") in " << BOXES_ARRAY << "\n";
            return nullptr;
        }

        std::cout << "Box = " << *(boxItem->second.as_string()) << "\n";

        auto childrenItem = boxTable->find(CHILDREN_ITEM);
        if (childrenItem == boxTable->end()) {
            // Box item doesn't have any children, so just continue on to the next item
            continue;
        }

        auto childTab = childrenItem->second.as_array();
        for (auto cIter = childTab->begin(); cIter != childTab->end(); cIter++) {
            std::cout << "Child = " << *(cIter->as_string()) << "\n";
        }
    }

    return &_boxConfig;
}