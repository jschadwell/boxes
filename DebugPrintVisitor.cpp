#include "DebugPrintVisitor.h"
#include "Box.h"
#include <iostream>

void DebugPrintVisitor::visitBox(Box* box) {
    std::cout << "Box.name = " << box->getName() << "\n";
    std::cout << "Box.width = " << box->getWidth() << "\n";
    std::cout << "Box.height = " << box->getHeight() << "\n";
    std::cout << "Box.orientation = " << ((box->getOrientation() == Box::Orientation::horizontal) ? "horizontal" : "vertical") << "\n";
    std::cout << "\n";
}