#include "BoxConfiguration.h"
#include <iostream>

BoxConfiguration::BoxConfiguration(std::string id) : _id(id) {}

bool BoxConfiguration::addChild(std::string id) {
	if (_id.empty()) {
		return false;
	}

	auto status = _children.insert(id);
	return status.second;
}

const ChildSet& BoxConfiguration::getChildren() const {
	return _children;
}

void BoxConfiguration::print() {
    std::cout << "Box ID = " << _id << std::endl;
    for (auto&& child : _children) {
    	std::cout << "    Child = " << child << std::endl;
    }
}