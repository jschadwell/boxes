#include "PrettyPrintVisitor.h"
#include "Box.h"
#include <iostream>

const char CORNER = '+';
const char VERTICAL_EDGE = '|';
const char HORIZONTAL_EDGE = '-';
const char BLANK = ' ';

void PrettyPrintVisitor::visitBox(Box* box) {
    
}

void PrettyPrintVisitor::printBoxes() {
    PrintInstruction test[] = {
        { std::string("box1"), 0, 0, 0, CORNER },
        { std::string("box1"), 1, 1, 0, HORIZONTAL_EDGE },
        { std::string("box1"), 2, 2, 0, CORNER },
        { std::string("box1"), 0, 0, 1, VERTICAL_EDGE },
        { std::string("box1"), 1, 1, 1, BLANK },
        { std::string("box1"), 2, 2, 1, VERTICAL_EDGE },
        { std::string("box1"), 0, 0, 2, CORNER },
        { std::string("box1"), 1, 1, 2, HORIZONTAL_EDGE },
        { std::string("box1"), 2, 2, 2, CORNER }
    };

    int curX = 0;
    int curY = 0;
    int i = 0;
    while (i < sizeof(test)/sizeof(test[0])) {
        if (curY < test[i].y) {
            std::cout << "\n";
            curX = 0;
            curY++;
        }
        if (curX >= test[i].startX && curX <= test[i].endX) {
            std::cout << test[i].ch;
        }
        curX++;
    }
    std::cout << "\n";
}