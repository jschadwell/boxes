#include "NestedBoxBuilder.h"
#include <boost/property_tree/xml_parser.hpp>
#include <exception>
#include <iostream>

NestedBoxBuilder::NestedBoxBuilder() {}

NestedBoxBuilder::~NestedBoxBuilder() {}

bool NestedBoxBuilder::load(std::string& xmlFile) {
	// Parse the XML file into a property tree
	try {
		pt::read_xml(xmlFile, _tree);
	} catch (pt::xml_parser::xml_parser_error& e) {
		std::cerr << e.what() << std::endl;
		return false;
	}

	return true;
}

bool NestedBoxBuilder::buildNestedBox() {
	return true;
}

Box* NestedBoxBuilder::getNestedBox() {
	return nullptr;
}