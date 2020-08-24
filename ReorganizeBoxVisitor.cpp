#include "ReorganizeBoxVisitor.h"
#include <cstdlib>
#include <utility>
#include <numeric>

void ReorganizeBoxVisitor::visitBox(Box* box) {
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
    // to set the xOffset to point to the end instead of the beginning, then
    // subtract out the width of the last box to ensure that xOffset is
    // pointing to the correct box.
    int xOffset = std::accumulate(box->rbegin(), box->rend(), 0,
        [](int a, const BoxUPtr& b) {
            return a + b->getWidth() + 1;
        });
    auto cIter = box->rbegin();
    xOffset -= (*cIter)->getWidth() + 1;
    cIter++;

    for (auto iter = _visited.rbegin(); iter != _visited.rend() && !box->isSiblingOf((*iter)->getName()); iter++) {
        if (cIter != box->rend() && (*cIter)->getName() == (*iter)->getName()) {
            xOffset -= ((*cIter)->getWidth() + 1);
            if (cIter + 1 != box->rend()) {
                cIter++;
            }
        }

        (*iter)->setX((*iter)->getX() + xOffset);

        if (cIter == box->rend()) {
            return;
        }
    }
}

void ReorganizeBoxVisitor::repositionChildrenVertically(Box* box) {
    // Since we're iterating over the visited boxes in reverse order, we need
    // to set the yOffset to point to the end instead of the beginning, then
    // subtract out the height of the last box to ensure that yOffset is
    // pointing to the correct box.
    int yOffset = std::accumulate(box->rbegin(), box->rend(), 0,
        [](int a, const BoxUPtr& b) {
            return a + b->getHeight();
        });
    auto cIter = box->rbegin();
    yOffset -= (*cIter)->getHeight();
    cIter++;

    for (auto iter = _visited.rbegin(); iter != _visited.rend() && !box->isSiblingOf((*iter)->getName()); iter++) {
        if (cIter != box->rend() && (*cIter)->getName() == (*iter)->getName()) {
            yOffset -= (*cIter)->getHeight();
            if (cIter + 1 != box->rend()) {
                cIter++;
            }
        }

        (*iter)->setY((*iter)->getY() + yOffset);

        if (cIter == box->rend()) {
            return;
        }
    }
}

const int X_CHILD_OFFSET = 2;   // Account for vertical edge + space
const int Y_CHILD_OFFSET = 1;   // Account for horizontal edge

void ReorganizeBoxVisitor::repositionChildrenInBox(Box* box) {
    for (auto iter = _visited.rbegin(); iter != _visited.rend() && !box->isSiblingOf((*iter)->getName()); iter++) {
        (*iter)->setX((*iter)->getX() + X_CHILD_OFFSET);
        (*iter)->setY((*iter)->getY() + Y_CHILD_OFFSET);
    }
}