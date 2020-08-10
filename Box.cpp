#include "Box.h"
#include <iostream>

Box::Box(std::string id) : _id(id) {}

bool Box::addChild(std::string id) {
	if (_id.empty()) {
		return false;
	}

	auto status = _children.insert(id);
	return status.second;
}

void Box::print() {
    std::cout << "Box ID = " << _id << std::endl;
    for (auto&& child : _children) {
    	std::cout << "    Child = " << child << std::endl;
    }
}