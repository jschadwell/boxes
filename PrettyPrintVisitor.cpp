#include "PrettyPrintVisitor.h"
#include "Box.h"
#include <iostream>
#include <algorithm>

const char CORNER = '+';
const char VERTICAL_EDGE = '|';
const char HORIZONTAL_EDGE = '-';
const char BLANK = ' ';

const int DEFAULT_X_ORIGIN = 0;
const int DEFAULT_Y_ORIGIN = 0;
const int X_CHILD_OFFSET = 2;   // Account for vertical edge + space
const int Y_CHILD_OFFSET = 1;   // Account for horizontal edge

void PrettyPrintVisitor::visitBox(Box* box) {
    int width = box->getWidth();
    int height = box->getHeight();
    std::string name = box->getName();
    for (int y = 0; y < height; y++) {
        if (y == 0 || y == height - 1) {
            // Print instructions for the top and bottom
            _instructions.push_back(std::make_unique<PrintInstruction>(PrintInstruction( { name, DEFAULT_X_ORIGIN, 0, y, CORNER } )));
            _instructions.push_back(std::make_unique<PrintInstruction>(PrintInstruction( { name, DEFAULT_X_ORIGIN + 1, width - 2, y, HORIZONTAL_EDGE } )));
            _instructions.push_back(std::make_unique<PrintInstruction>(PrintInstruction( { name, width - 1, width - 1, y, CORNER } )));
        } else {
            // Print instructions for the sides
            _instructions.push_back(std::make_unique<PrintInstruction>(PrintInstruction( { name, DEFAULT_X_ORIGIN, 0, y, VERTICAL_EDGE } )));
            _instructions.push_back(std::make_unique<PrintInstruction>(PrintInstruction( { name, width - 1, width - 1, y, VERTICAL_EDGE } )));
        }
    }

    if (!box->hasChildren()) {
        // Box has no children, so no x, y coordinate adjustments are necessary
        return;
    }

    for (auto iter = _instructions.rbegin(); iter != _instructions.rend() && !box->isSiblingOf((*iter)->boxName); iter++) {
        (*iter)->startX += X_CHILD_OFFSET;
        (*iter)->endX += X_CHILD_OFFSET;
        (*iter)->y += Y_CHILD_OFFSET;
    }
}

void PrettyPrintVisitor::printBoxes() {
    // PrintInstruction test[] = {
    //     { std::string("box1"), 0, 0, 0, CORNER },
    //     { std::string("box1"), 1, 5, 0, HORIZONTAL_EDGE },
    //     { std::string("box1"), 6, 6, 0, CORNER },

    //     { std::string("box1"), 0, 0, 1, VERTICAL_EDGE },
    //     { std::string("box2"), 2, 2, 1, CORNER },
    //     { std::string("box2"), 3, 3, 1, HORIZONTAL_EDGE },
    //     { std::string("box2"), 4, 4, 1, CORNER },
    //     { std::string("box2"), 6, 6, 1, VERTICAL_EDGE },
    //     { std::string("box1"), 0, 0, 2, VERTICAL_EDGE },
    //     { std::string("box2"), 2, 2, 2, VERTICAL_EDGE },
    //     { std::string("box2"), 4, 4, 2, VERTICAL_EDGE },
    //     { std::string("box2"), 6, 6, 2, VERTICAL_EDGE },
    //     { std::string("box1"), 0, 0, 3, VERTICAL_EDGE },
    //     { std::string("box2"), 2, 2, 3, CORNER },
    //     { std::string("box2"), 3, 3, 3, HORIZONTAL_EDGE },
    //     { std::string("box2"), 4, 4, 3, CORNER },
    //     { std::string("box2"), 6, 6, 3, VERTICAL_EDGE },

    //     { std::string("box1"), 0, 0, 4, CORNER },
    //     { std::string("box1"), 1, 5, 4, HORIZONTAL_EDGE },
    //     { std::string("box1"), 6, 6, 4, CORNER }
    // };

    // for (int i = 0; i < sizeof(test)/sizeof(test[0]); ++i) {
    //     _instructions.push_back(std::make_unique<PrintInstruction>(test[i]));
    // }

    std::sort(_instructions.begin(), _instructions.end(),
        [](const std::unique_ptr<PrintInstruction>& lhs, const std::unique_ptr<PrintInstruction>& rhs) {
            if (lhs->y == rhs->y) {
                return lhs->startX < rhs->startX;
            } else {
                return lhs->y < rhs->y;
            }
        });

    for (auto iter = _instructions.begin(); iter != _instructions.end(); iter++) {
        std::cout << (*iter)->boxName << ", startX = " << (*iter)->startX << ", y = " << (*iter)->y << "\n";
    }


    int curX = 0;
    int curY = 0;
    auto iter = _instructions.begin();
    while (iter != _instructions.end()) {
        if (curY < (*iter)->y) {
            std::cout << "\n";
            curX = 0;
            curY++;
        }
        if (curX < (*iter)->startX) {
            std::cout << BLANK;
            curX++;
        } else if (curX > (*iter)->endX) {
            iter++;
        } else {
            std::cout << (*iter)->ch;
            curX++;
        }

    }
    std::cout << "\n";
}