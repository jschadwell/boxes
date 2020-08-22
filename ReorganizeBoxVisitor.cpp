#include "ReorganizeBoxVisitor.h"
#include "Box.h"
#include <cstdlib>
#include <iostream>
#include <utility>

void ReorganizeBoxVisitor::visitBox(Box* box) {
    int width = box->getWidth();
    int height = box->getHeight();

    std::cout << "Box (" << box->getName() << ")" << "\n";
    std::cout << "    Orientation = " << (box->getOrientation() == Box::Orientation::vertical ? "vertical" : "horizontal") << "\n";
    if (box->getOrientation() == Box::Orientation::horizontal) {
        makeHorizontalStack(box, width, height);
    } else {
        makeVerticalStack(box, width, height);
    }
    std::cout << "    width = " << width << ", height = " << height << "\n";
    std::cout << "\n";

    box->setWidth(width);
    box->setHeight(height);
}

void ReorganizeBoxVisitor::makeHorizontalStack(Box* box, int& width, int& height) {
    if (!box->hasChildren()) {
        // We're done, so just return
        return;
    }

    height = Box::MIN_HEIGHT - 1;
    for (auto childIter = box->begin(); childIter != box->end(); childIter++) {
        width += (*childIter)->getWidth() + 1; // The extra 1 is to account for the spacers between the boxes
        int tempHeight = (*childIter)->getHeight() + (Box::MIN_HEIGHT - 1); // No spacers in the height;
        height = (tempHeight > height) ? tempHeight : height;
    }
}

void ReorganizeBoxVisitor::makeVerticalStack(Box* box, int& width, int& height) {
    if (!box->hasChildren()) {
        // We're done, so just return
        return;
    }

    height = Box::MIN_HEIGHT - 1;
    for (auto childIter = box->begin(); childIter != box->end(); childIter++) {
        int tempWidth = (*childIter)->getWidth() + (Box::MIN_WIDTH + 1); // The extra 1 is to account for the spacers
        width = (tempWidth > width) ? tempWidth : width;
        height += (*childIter)->getHeight();
    }
}