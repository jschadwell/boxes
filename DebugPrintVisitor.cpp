#include "DebugPrintVisitor.h"
#include "Box.h"
#include <iostream>

void DebugPrintVisitor::visitBox(Box* box) {
    std::cout << "Box = " << box->getName() << "\n";
}