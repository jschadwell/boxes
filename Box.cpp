#include "Box.h"

Box::Box() : _parent(nullptr) {}

void Box::addParent(Box* parent) {
	_parent = parent;
}

void Box::addChild(Box* child) {
	_children.push_back(child);
}