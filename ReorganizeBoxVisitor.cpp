#include "ReorganizeBoxVisitor.h"
#include <cstdlib>
#include <iostream>
#include <utility>
#include <numeric>

void ReorganizeBoxVisitor::visitBox(Box* box) {
    std::cout << "Visiting " << box->getName() << "\n";
    int width = box->getWidth();
    int height = box->getHeight();

    if (box->hasChildren()) {
        if (box->getOrientation() == Box::Orientation::horizontal) {
            makeHorizontalStack(box, width, height);
            repositionChildrenHorizontally(box);
        } else {
            makeVerticalStack(box, width, height);
            repositionChildrenVertically(box);
        }
        repositionChildrenInBox(box);
    }

    box->setWidth(width);
    box->setHeight(height);
    _visited.push_back(box);
    std::cout << "\n";
}

void ReorganizeBoxVisitor::makeHorizontalStack(Box* box, int& width, int& height) {
    height = Box::MIN_HEIGHT - 1;
    for (auto childIter = box->begin(); childIter != box->end(); childIter++) {
        width += (*childIter)->getWidth() + 1; // The extra 1 is to account for the spacers between the boxes
        int tempHeight = (*childIter)->getHeight() + (Box::MIN_HEIGHT - 1); // No spacers in the height;
        height = (tempHeight > height) ? tempHeight : height;
    }
}

void ReorganizeBoxVisitor::makeVerticalStack(Box* box, int& width, int& height) {
    height = Box::MIN_HEIGHT - 1;
    for (auto childIter = box->begin(); childIter != box->end(); childIter++) {
        int tempWidth = (*childIter)->getWidth() + (Box::MIN_WIDTH + 1); // The extra 1 is to account for the spacers
        width = (tempWidth > width) ? tempWidth : width;
        height += (*childIter)->getHeight();
    }
}

void ReorganizeBoxVisitor::repositionChildrenHorizontally(Box* box) {
    // Since we're iterating over the visited boxes in reverse order, we need
    // to set the xOffset to point to the end instead of the beginning
    auto cIter = box->rbegin();
    cIter++;
    int xOffset = std::accumulate(cIter, box->rend(), 1,
        [](int a, const BoxUPtr& b) {
            return a + b->getWidth() + 1;
        });

    cIter = box->rbegin();
    for (auto iter = _visited.rbegin(); iter != _visited.rend() && !box->isSiblingOf((*iter)->getName()); iter++) {
        if (cIter == box->rend()) {
            return;
        }

        std::cout << "    box = " << (*iter)->getName() << "\n";
        std::cout << "    child = " << (*cIter)->getName() << "\n";
        std::cout << "    xOffset = " << xOffset << "\n";
        (*iter)->setX((*iter)->getX() + xOffset);
        std::cout << "    x = " << (*iter)->getX() << "\n";
        std::cout << "    y = " << (*iter)->getY() << "\n";
        std::cout << "\n";

        if ((*cIter)->getName() == (*iter)->getName()) {
            xOffset -= ((*cIter)->getWidth() - 1);
            cIter++;
        }
    }
}

void ReorganizeBoxVisitor::repositionChildrenVertically(Box* box) {
    // Since we're iterating over the visited boxes in reverse order, we need
    // to set the yOffset to point to the end instead of the beginning
    auto cIter = box->rbegin();
    cIter++;
    int yOffset = std::accumulate(cIter, box->rend(), 0,
        [](int a, const BoxUPtr& b) {
            return a + b->getHeight();
        });

    cIter = box->rbegin();
    for (auto iter = _visited.rbegin(); iter != _visited.rend() && !box->isSiblingOf((*iter)->getName()); iter++) {
        if (cIter == box->rend()) {
            return;
        }

        std::cout << "    box = " << (*iter)->getName() << "\n";
        std::cout << "    child = " << (*cIter)->getName() << "\n";
        std::cout << "    yOffset = " << yOffset << "\n";
        (*iter)->setY((*iter)->getY() + yOffset);
        std::cout << "    x = " << (*iter)->getX() << "\n";
        std::cout << "    y = " << (*iter)->getY() << "\n";
        std::cout << "\n";

        if ((*cIter)->getName() == (*iter)->getName()) {
            yOffset -= (*cIter)->getHeight();
            cIter++;
        }
    }
}

const int X_CHILD_OFFSET = 2;   // Account for vertical edge + space
const int Y_CHILD_OFFSET = 1;   // Account for horizontal edge

void ReorganizeBoxVisitor::repositionChildrenInBox(Box* box) {
    for (auto iter = _visited.rbegin(); iter != _visited.rend() && !box->isSiblingOf((*iter)->getName()); iter++) {
        (*iter)->setX((*iter)->getX() + X_CHILD_OFFSET);
        (*iter)->setY((*iter)->getY() + Y_CHILD_OFFSET);;
    }
}