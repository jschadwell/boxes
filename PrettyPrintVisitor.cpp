#include "PrettyPrintVisitor.h"
#include "Box.h"
#include <iostream>
#include <algorithm>
#include <numeric>

const char CORNER = '+';
const char VERTICAL_EDGE = '|';
const char HORIZONTAL_EDGE = '-';
const char BLANK = ' ';

void PrettyPrintVisitor::visitBox(Box* box) {
    int width = box->getWidth();
    int height = box->getHeight();
    std::string name = box->getName();
    for (int y = 0; y < height; y++) {
        if (y == 0 || y == height - 1) {
            // Print instructions for the top and bottom
            _instructions.push_back(std::make_unique<PrintInstruction>(PrintInstruction( { name, box->getX(), 0, y, CORNER } )));
            _instructions.push_back(std::make_unique<PrintInstruction>(PrintInstruction( { name, box->getX() + 1, width - 2, y, HORIZONTAL_EDGE } )));
            _instructions.push_back(std::make_unique<PrintInstruction>(PrintInstruction( { name, width - 1, width - 1, y, CORNER } )));
        } else {
            // Print instructions for the sides
            _instructions.push_back(std::make_unique<PrintInstruction>(PrintInstruction( { name, box->getX(), 0, y, VERTICAL_EDGE } )));
            _instructions.push_back(std::make_unique<PrintInstruction>(PrintInstruction( { name, width - 1, width - 1, y, VERTICAL_EDGE } )));
        }
    }
}

void PrettyPrintVisitor::printBoxes() {
    // Sort the instructions into the correct order - by y, then by x
    std::stable_sort(_instructions.begin(), _instructions.end(),
        [](const std::unique_ptr<PrintInstruction>& lhs, const std::unique_ptr<PrintInstruction>& rhs) {
            if (lhs->y == rhs->y) {
                return lhs->startX < rhs->startX;
            } else {
                return lhs->y < rhs->y;
            }
        });

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