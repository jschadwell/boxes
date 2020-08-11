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

	auto pos = std::find(std::begin(_children), std::end(_children), id);
	if (pos != std::end(_children)) {
		return false;
	}

	_children.push_back(id);
	return true;
}

BoxConfigurationIterator BoxConfiguration::begin() {
	return std::begin(_children);
}

BoxConfigurationIterator BoxConfiguration::end() {
	return std::end(_children);
}