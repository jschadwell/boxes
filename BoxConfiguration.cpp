#include "BoxConfiguration.h"
#include <iostream>
#include <algorithm>

BoxConfiguration::BoxConfiguration(std::string name) : _name(name) {}

std::string& BoxConfiguration::getName() {
	return _name;
}

bool BoxConfiguration::addChild(std::string name) {
	if (name.empty()) {
		return false;
	}

	auto pos = std::find(std::begin(_children), std::end(_children), name);
	if (pos != std::end(_children)) {
		return false;
	}

	_children.push_back(name);
	return true;
}

BoxConfigurationIterator BoxConfiguration::begin() {
	return std::begin(_children);
}

BoxConfigurationIterator BoxConfiguration::end() {
	return std::end(_children);
}