#include "NestedBoxBuilder.h"
#include <boost/property_tree/xml_parser.hpp>
#include <vector>
#include <iostream>

NestedBoxBuilder::NestedBoxBuilder() {}

NestedBoxBuilder::~NestedBoxBuilder() {}

bool NestedBoxBuilder::loadConfigFile(std::string& xmlFile) {
	// Parse the XML file into a property tree
	try {
		pt::read_xml(xmlFile, _tree);
	} catch (const pt::xml_parser::xml_parser_error& e) {
		errorMsg(e);
		return false;
	}

	return true;
}

bool NestedBoxBuilder::buildNestedBox() {
	std::vector<std::unique_ptr<BoxParams> > boxParamList;

	// Pass 1 - parse all of the box IDs
	if (!parseConfigFile()) {
		return false;
	}

	// Pass 2 - parse all of the parent/child relationships
	if (!parseParents()) {
		return false;
	}

	for (auto&& box : _boxMap) {
		box.second->print();
	}

	return true;
}

bool NestedBoxBuilder::parseConfigFile() {
	try {
		for (const pt::ptree::value_type& v : _tree.get_child("nestconfig")) {
			if (v.first == "box") {
				std::string id = v.second.get<std::string>("<xmlattr>.id");
				if (id == "") {
					throw pt::ptree_error("Box element with empty ID encountered");
				}
				
				if (_boxMap.find(id) != end(_boxMap)) {
					// Duplicate element found
					throw pt::ptree_error("Duplicate xml element (" + id + ") found");
				}
				// Insert the new element into the map
				_boxMap[id] = std::make_unique<Box>(id);
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

bool NestedBoxBuilder::parseParents() {
	return true;
}

Box* NestedBoxBuilder::getNestedBox() {
	return nullptr;
}

void NestedBoxBuilder::errorMsg(const std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
}