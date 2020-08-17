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
	if (_children.size() == 0) {
		// We only need to resize the box if it has children
		return;
	}

	int newWidth = 0;
	int newHeight = 0;
	int horizW = _width;	// Width for horizontal bounding box
	int horizH = _height;	// Height for horizontal bounding box
	int vertW = _width;	// Width for vertical bounding box
	int vertH = _height;	// Height for vertical bounding box
	int maxW = 0;
	int maxH = 0;
	std::cout << "Box[" << _id << "]: old width = " << _width << ", old height = " << _height << std::endl;
	for (auto&& child : _children) {
		child->resize();
		// HorizW already has one space built in, but we also need to account for the additional
		// space after each child box, so we add have to add 1 after each box.
		horizW += child->getWidth() + 1;
		// Since the extra spaces don't come into play vertically, we need to account for this,
		// so we subtract out the extra space. Note that we're not
		horizH = _height + child->getHeight() - 1;
		vertW = _width + child->getWidth() + 1;
		vertH += child->getHeight();
	}
	vertH -= 1;
	std::cout << "Box[" << _id << "]: tempW1 = " << horizW << ", tempH1 = " << horizH << std::endl;
	std::cout << "Box[" << _id << "]: tempW2 = " << vertW << ", tempH2 = " << vertH << std::endl;

	// Determine which bounding box is "more square"
	int diff1 = std::abs(horizW - horizH);
	int diff2 = std::abs(vertW - vertH);
	if (diff2 < diff1) {
		_orientation = Orientation::vertical;
		newWidth = vertW;
		newHeight = vertH;
	} else {
		_orientation = Orientation::horizontal;
		newWidth = horizW;
		newHeight = horizH;
	}
	std::cout << "Box[" << _id << "]: updated width = " << newWidth << ", updated height = " << newHeight << std::endl;
	_width = newWidth;
	_height = newHeight;
}

void Box::print() {
	std::cout << "Box[" << _id << "]: width = " << _width << ", height = " << _height << std::endl;
	for (auto&& child :_children) {
		child->print();
	}
}