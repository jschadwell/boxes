#include "Box.h"
#include <iostream>
#include <cmath>

const int MIN_WIDTH = 3;
const int MIN_HEIGHT = 3;

Box::Box(std::string name, Box::Orientation o)
	: _name(name),
	  _parent(nullptr),
	  _x(0),
	  _y(0),
	  _width(Box::MIN_WIDTH),
	  _height(Box::MIN_HEIGHT),
	  _orientation(o) {
}

std::string& Box::getName() {
	return _name;
}

void Box::setParent(Box* box) {
	_parent = box;
}

Box* Box::getParent() {
	return _parent;
}

void Box::setX(int x) {
	_x = x;
}

int Box::getX() {
	return _x;
}

void Box::setY(int y) {
	_y = y;
}

int Box::getY() {
	return _y;
}

void Box::setWidth(int w) {
	_width = w;
}

int Box::getWidth() {
	return _width;
}

void Box::setHeight(int h) {
	_height = h;
}

int Box::getHeight() {
	return _height;
}

void Box::setOrientation(Box::Orientation o) {
	_orientation = o;
}

Box::Orientation Box::getOrientation() {
	return _orientation;
}

BoxIter Box::begin() {
	return _children.begin();
}

BoxIter Box::end() {
	return _children.end();
}

BoxReverseIter Box::rbegin() {
	return _children.rbegin();
}

BoxReverseIter Box::rend() {
	return _children.rend();
}

void Box::addChild(Box* child) {
	_children.push_back(BoxUPtr(child));
}

Box* Box::getChild(std::string& name) {
	for (auto iter = _children.begin(); iter != _children.end(); iter++) {
		if (name == (*iter)->getName()) {
			return iter->get();
		}
	}

	return nullptr;
}

bool Box::hasChild(std::string& name) {
	for (auto iter = _children.begin(); iter != _children.end(); iter++) {
		if (name == (*iter)->getName()) {
			return true;
		}
	}

	return false;
}

bool Box::hasChildren() {
	return _children.size() > 0;
}

bool Box::isSiblingOf(std::string& name) {
	// Make sure we're not checking if the box is its own sibling
	if (name == _name) {
		return false;
	}

	// Make sure the box has a parent
	if (_parent == nullptr) {
		return false;
	}

	return _parent->hasChild(name);
}

void Box::accept(AbstractBoxVisitor& visitor) {
	for (auto iter = _children.begin(); iter != _children.end(); iter++) {
		(*iter)->accept(visitor);
	}
	visitor.visitBox(this);
}