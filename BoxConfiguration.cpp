#include "BoxConfiguration.h"
#include <iostream>
#include <algorithm>

BoxConfiguration::BoxConfiguration(std::string id) : _id(id) {}

std::string& BoxConfiguration::getId() {
	return _id;
}

bool BoxConfiguration::addChild(std::string id) {
	if (_id.empty()) {
		return false;
	}

	auto pos = std::find(begin(_children), end(_children), id);
	if (pos != end(_children)) {
		return false;
	}

	_children.push_back(id);
	return true;
}

const std::vector<std::string>& BoxConfiguration::getChildren() const {
	return _children;
}