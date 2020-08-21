#include "Box.h"
#include <iostream>
#include <cmath>

const unsigned int defaultWidth = 3;
const unsigned int defaultHeight = 3;

Box::Box(std::string name) : _name(name), _width(defaultWidth), _height(defaultHeight) {}

std::string& Box::getName() {
	return _name;
}

void Box::setWidth(unsigned int width) {
	_width = width;
}

unsigned int Box::getWidth() {
	return _width;
}

void Box::setHeight(unsigned int height) {
	_height = height;
}

unsigned int Box::getHeight() {
	return _height;
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