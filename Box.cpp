#include "Box.h"
#include <iostream>
#include <cmath>

const int defaultWidth = 3;
const int defaultHeight = 3;

Box::Box(std::string name) : _name(name) {}

std::string& Box::getName() {
	return _name;
}

BoxIter Box::begin() {
	return _children.begin();
}

BoxIter Box::end() {
	return _children.end();
}

void Box::addChild(Box* child) {
	_children.push_back(BoxUPtr(child));
}

bool Box::hasChildren() {
	return _children.size() > 0;
}

void Box::accept(AbstractBoxVisitor& visitor) {
	for (auto iter = _children.begin(); iter != _children.end(); iter++) {
		(*iter)->accept(visitor);
	}
	visitor.visitBox(this);
}