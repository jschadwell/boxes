#include "Box.h"
#include <iostream>
#include <cmath>

const int defaultWidth = 3;
const int defaultHeight = 3;

Box::Box(std::string id) : _id(id), _width(defaultWidth), _height(defaultHeight), _orientation(Orientation::vertical), _parent(nullptr) {}

void Box::addParent(Box* parent) {
	_parent = parent;
}

Box* Box::getParent() {
	return _parent;
}

void Box::addChild(Box* child) {
	_children.push_back(child);
}

std::vector<Box*>& Box::getChildren() {
	return _children;
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

void Box::setOrientation(Orientation o) {
	_orientation = o;
}

Orientation Box::getOrientation() {
	return _orientation;
}

void Box::resize() {
	int newWidth = 0;
	int newHeight = 0;
	int tempW1 = _width;	// Width for horizontal bounding box
	int tempW2 = _width;	// Width for vertical bounding box
	int tempH1 = _height;	// Height for horizontal bounding box
	int tempH2 = _height - 1;	// Height for vertical bounding box
	std::cout << "old width = " << _width << ", old height = " << _height << std::endl;
	for (auto&& child : _children) {
		child->resize();
		tempW1 += child->getWidth() + 1;	// We add 1 here to account for the space between each box
		tempH1 = _height + child->getHeight() - 1;
		tempW2 = _width + child->getWidth() + 1;
		tempH2 += child->getHeight();
	}
	std::cout << "tempW1 = " << tempW1 << ", tempH1 = " << tempH1 << std::endl;
	std::cout << "tempW2 = " << tempW2 << ", tempH2 = " << tempH2 << std::endl;

	// Determine which bounding box is "more square"
	int diff1 = std::abs(tempW1 - tempH1);
	int diff2 = std::abs(tempW2 - tempH2);
	if (diff2 < diff1) {
		_orientation = Orientation::vertical;
		newWidth = tempW2;
		newHeight = tempH2;
	} else {
		_orientation = Orientation::horizontal;
		newWidth = tempW1;
		newHeight = tempH1;
	}
	std::cout << "updated width = " << newWidth << ", updated height = " << newHeight << std::endl;
	_width = newWidth;
	_height = newHeight;
}

void Box::print() {
	std::cout << "Box[" << _id << "], width = " << _width << ", height = " << _height << std::endl;
	for (auto&& child :_children) {
		child->print();
	}
}