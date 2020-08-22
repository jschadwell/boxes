#include "ReorganizeBoxVisitor.h"
#include "Box.h"
#include <cstdlib>
#include <iostream>
#include <utility>

const int MIN_WIDTH = 3;
const int MIN_HEIGHT = 3;

void ReorganizeBoxVisitor::visitBox(Box* box) {
    int horzWidth = 0;
    int horzHeight = 0;
    int vertWidth = 0;
    int vertHeight = 0;

    std::cout << "Box (" << box->getName() << ")" << "\n";
    makeHorizontalStack(box, horzWidth, horzHeight);
    makeVerticalStack(box, vertWidth, vertHeight);
    std::cout << "    Horizontal width = " << horzWidth << ", height = " << horzHeight << "\n";
    std::cout << "    Vertical width = " << vertWidth << ", height = " << vertHeight << "\n";
    std::cout << "\n";

    _horzBoxMap.insert(std::pair<std::string, std::unique_ptr<BoxParm> >(box->getName(), std::make_unique<BoxParm>(horzWidth, horzHeight)));
    _vertBoxMap.insert(std::pair<std::string, std::unique_ptr<BoxParm> >(box->getName(), std::make_unique<BoxParm>(vertWidth, vertHeight)));

    // Get the difference between the width and the height to figure out
    // which orientation is more "square." The smaller the difference, the
    // more square it is.
    // int horzDiff = abs(horzWidth - horzHeight);
    // int vertDiff = abs(vertWidth - vertHeight);

    // if (vertDiff < horzDiff) {
    //     box->setWidth(horzWidth);
    //     box->setHeight(horzHeight);
    //     box->setOrientation(Box::Orientation::horizontal);
    // } else {
    //     box->setWidth(vertWidth);
    //     box->setHeight(vertHeight);
    //     box->setOrientation(Box::Orientation::vertical);
    // }
}

void ReorganizeBoxVisitor::makeHorizontalStack(Box* box, int& width, int& height) {
    // Make an empty box with the correct dimensions to make it look like this
    // when it's displayed:
    // 
    //     +-+
    //     | |
    //     +-+
    //    
    width = MIN_WIDTH;
    height = MIN_HEIGHT;

    if (!box->hasChildren()) {
        // We're done, so just return
        return;
    }

    // Since we have child boxes, we have to calculate the width and length. In this case,
    // the empty box is going to look like this:
    //
    //     +-+
    //     +-+
    //
    // By the time we're done, it will be filled in correctly.
    height = MIN_HEIGHT - 1;
    for (auto childIter = box->begin(); childIter != box->end(); childIter++) {
        // width += (*childIter)->getWidth() + 1; // The extra 1 is to account for the spacers between the boxes
        // int tempHeight = (*childIter)->getHeight() + (MIN_HEIGHT - 1); // No spacers in the height;
        // height = (tempHeight > height) ? tempHeight : height;
        auto childName = (*childIter)->getName();
        width += _vertBoxMap.at(childName)->width + 1;
        int tempHeight = _vertBoxMap.at(childName)->height + (MIN_HEIGHT - 1);
        height = (tempHeight > height) ? tempHeight : height;
    }
}

void ReorganizeBoxVisitor::makeVerticalStack(Box* box, int& width, int& height) {
    // Make an empty box with the correct dimensions to make it look like this
    // when it's displayed:
    // 
    //     +-+
    //     | |
    //     +-+
    //    
    width = MIN_WIDTH;
    height = MIN_HEIGHT;

    if (!box->hasChildren()) {
        // We're done, so just return
        return;
    }

    // Since we have child boxes, we have to calculate the width and length. In this case,
    // the empty box is going to look like this:
    //
    //     +-+
    //     +-+
    //
    // By the time we're done, it will be filled in correctly.
    height = MIN_HEIGHT - 1;
    for (auto childIter = box->begin(); childIter != box->end(); childIter++) {
        // int tempWidth = (*childIter)->getWidth() + (MIN_WIDTH + 1); // The extra 1 is to account for the spacers
        // width = (tempWidth > width) ? tempWidth : width;
        // height += (*childIter)->getHeight();
        auto childName = (*childIter)->getName();
        int tempWidth = _horzBoxMap.at(childName)->width + (MIN_WIDTH + 1);
        width = (tempWidth > width) ? tempWidth : width;
        height += _horzBoxMap.at(childName)->height;
    }
}