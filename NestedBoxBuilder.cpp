#include "NestedBoxBuilder.h"
#include <boost/property_tree/xml_parser.hpp>
#include <vector>
#include <iostream>

// For storing box parameters extracted from the XML config file
struct BoxParams {
	std::string id;
	bool hasParent = false;
	std::vector<std::string> children;
};

NestedBoxBuilder::NestedBoxBuilder() {}

NestedBoxBuilder::~NestedBoxBuilder() {}

bool NestedBoxBuilder::load(std::string& xmlFile) {
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
	try {
		for (const pt::ptree::value_type& v : _tree.get_child("nestconfig")) {
			if (v.first == "box") {
				std::string id = v.second.get<std::string>("<xmlattr>.id");
				if (id == "") {
					throw pt::ptree_error("Box element with empty ID encountered");
				}
				std::cout << "Box ID = " << id << std::endl;
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

Box* NestedBoxBuilder::getNestedBox() {
	return nullptr;
}

void NestedBoxBuilder::errorMsg(const std::exception& e) {
	std::cerr << "Error: " << e.what() << std::endl;
}