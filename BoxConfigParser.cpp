#include "BoxConfigParser.h"
#include <set>
#include <iostream>
#include <fstream>
#include <cstring>

const char BOXES_ARRAY[] = "boxes";
const char BOX_ITEM[] = "box";
const char CHILDREN_ITEM[] = "children";

const char BOX_CONFIG_ELEMENT[] = "BoxConfig";
const char BOXES_ELEMENT[] = "Boxes";
const char BOX_ELEMENT[] = "Box";
const char PACKAGES_ELEMENT[] = "Packages";
const char PACKAGE_ELEMENT[] = "Package";
const char CHILDREN_ELEMENT[] = "Children";
const char CHILD_ELEMENT[] = "Child";
const char EMPTY_STRING[] = "";

bool BoxConfigParser::parse(char* configFile) {
    try {
        _config = toml::parse_file(configFile);
    } catch (const toml::parse_error& err) {
        std::cerr << "Error: " << err << "\n";
        return false;
    }

    for (auto iter = std::begin(_config); iter != std::end(_config); iter++) {
        std::cout << iter->first << "\n";
    }

    auto boxes = _config[BOXES_ARRAY];
    if (!boxes) {
        std::cerr << "Error: Unable to find (" << BOXES_ARRAY << ")" << "\n";
        return false;
    }

    toml::array* boxArray = boxes.as_array();
    for (auto iter = boxArray->begin(); iter != boxArray->end(); iter++) {
        toml::table* boxTable = iter->as_table();
        auto boxItem = boxTable->find(BOX_ITEM);
        if (boxItem == boxTable->end()) {
            std::cerr << "Error: Unable to find (" << BOX_ITEM << ") in " << BOXES_ARRAY << "\n";
            return false;
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

    return true;
}

bool BoxConfigParser::loadConfig(char* configFile) {
    // std::cout << "Loading " << configFile << std::endl;
    // pugi::xml_parse_result result = _configDoc.load_file(configFile);

    // if (!result) {
    //     std::cerr << "Error: " << result.description() << std::endl;
    //     return false;
    // }

    return true;
}

bool BoxConfigParser::validateConfig() {
    // // Validate document node
    // int numDocElements = 0;
    // for (pugi::xml_node docElement : _configDoc) {
    //     ++numDocElements;
    // }
    // if (numDocElements != 1) {
    //     std::cerr << "Error: Invalid number of document elements (" << numDocElements << ") found" << std::endl;
    //     return false;
    // }

    // pugi::xml_node docElement = _configDoc.child(BOX_CONFIG_ELEMENT);
    // if (!docElement) {
    //     std::cerr << "Error: Document element (" << BOX_CONFIG_ELEMENT << ") not found" << std::endl;
    //     return false;
    // }

    // // Validate children of document element
    // for (pugi::xml_node childElement : docElement) {
    //     if (std::strcmp(childElement.name(), BOXES_ELEMENT) != 0 && std::strcmp(childElement.name(), PACKAGES_ELEMENT) != 0) {
    //         std::cerr << "Error: Invalid element (" << childElement.name() << ") found" << std::endl;
    //         return false;
    //     }
    // }

    // // Validate box elements
    // pugi::xml_node boxesElement = docElement.child(BOXES_ELEMENT);
    // if (!boxesElement) {
    //     std::cerr << "Error: Element (" << BOXES_ELEMENT << ") not found" << std::endl;
    //     return false;
    // }
    // bool hasBoxElement = false;
    // std::set<std::string> boxSet;
    // for (pugi::xml_node boxElement = boxesElement.first_child(); boxElement; boxElement = boxElement.next_sibling()) {
    //     if (std::strcmp(boxElement.name(), BOX_ELEMENT) != 0) {
    //         std::cerr << "Error: Invalid element (" << boxElement.name() << ") found in (" << BOXES_ELEMENT << ")" << std::endl;
    //         return false;
    //     }
    //     if (std::strcmp(boxElement.child_value(), EMPTY_STRING) == 0) {
    //         std::cerr << "Error: Empty Box element encountered in (" << BOXES_ELEMENT << ")" << std::endl;
    //         return false;
    //     }
    //     hasBoxElement = true;

    //     std::string boxId(boxElement.child_value());
    //     if (boxSet.find(boxId) != std::end(boxSet)) {
    //         std::cerr << "Error: Duplicate Box element (" << boxId << ") found" << std::endl;
    //         return false;
    //     } else {
    //         boxSet.insert(boxId);
    //     }
    //     std::cout << "Box[" << boxId << "]" << std::endl;
    // }
    // if (!hasBoxElement) {
    //     std::cerr << "Error: Element (" << BOX_ELEMENT << ") not found in (" << BOXES_ELEMENT << ")" << std::endl;
    //     return false;
    // }

    // // Validate package elements
    // pugi::xml_node packagesElement = docElement.child(PACKAGES_ELEMENT);
    // if (!packagesElement) {
    //     std::cerr << "Error: Element (" << PACKAGES_ELEMENT << ") not found" << std::endl;
    //     return false;
    // }

    // for (pugi::xml_node packageElement = packagesElement.first_child(); packageElement; packageElement = packageElement.next_sibling()) {
    //     if (std::strcmp(packageElement.name(), PACKAGE_ELEMENT) != 0) {
    //         std::cerr << "Error: Invalid element (" << packageElement.name() << ") found in (" << PACKAGES_ELEMENT << ")" << std::endl;
    //         return false;
    //     }

    //     pugi::xml_node boxElement = packageElement.child(BOX_ELEMENT);
    //     if (!boxElement) {
    //         std::cerr << "Error: Element (" << BOX_ELEMENT << ") not found in (" << PACKAGE_ELEMENT << ")" << std::endl;
    //         return false;
    //     }

    //     pugi::xml_node childrenElement = packageElement.child(CHILDREN_ELEMENT);
    //     if (!childrenElement) {
    //         std::cerr << "Error: Element (" << CHILDREN_ELEMENT << ") not found in (" << PACKAGE_ELEMENT << ")" << std::endl;
    //         return false;
    //     }

    //     bool hasChildElement = false;
    //     std::set<std::string> childSet;
    //     for (pugi::xml_node childElement = childrenElement.first_child(); childElement; childElement = childElement.next_sibling()) {
    //         if (std::strcmp(childElement.name(), CHILD_ELEMENT) != 0) {
    //             std::cerr << "Error: Invalid element (" << childElement.name() << ") found in (" << CHILDREN_ELEMENT << ")" << std::endl;
    //             return false;
    //         }
    //         if (std::strcmp(childElement.child_value(), EMPTY_STRING) == 0) {
    //             std::cerr << "Error: Empty Child element encountered in (" << CHILDREN_ELEMENT << ")" << std::endl;
    //             return false;
    //         }

    //         hasChildElement = true;

    //         std::string childId(childElement.child_value());
    //         if (childSet.find(childId) != std::end(childSet)) {
    //             std::cerr << "Error: Duplicate Child element (" << childId << ") found" << std::endl;
    //             return false;
    //         } else {
    //             childSet.insert(childId);
    //         }
    //         if (!hasChildElement) {
    //             std::cerr << "Error: Element (" << CHILD_ELEMENT << ") not found in  (" << CHILDREN_ELEMENT << ")" << std::endl;
    //             return false;
    //         }
    //     }
    // }
    return true;
}