#include "box.h"
#include <iostream>

Box::Box() {}

Box::~Box() {}

//void Box::addChild(Box* child) {
//	std::unique_ptr<Box> p(child);
//	_children.push_back(p);
//}

//int numChildren() {
//	return _children.size();
//}

void Box::print() {
	std::cout << "print" << std::endl;
}