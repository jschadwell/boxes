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
        { std::string("box1"), 1, 5, 0, HORIZONTAL_EDGE },
        { std::string("box1"), 6, 6, 0, CORNER },

        { std::string("box1"), 0, 0, 1, VERTICAL_EDGE },
        { std::string("box1"), 1, 1, 1, BLANK },
        { std::string("box2"), 2, 2, 1, CORNER },
        { std::string("box2"), 3, 3, 1, HORIZONTAL_EDGE },
        { std::string("box2"), 4, 4, 1, CORNER },
        { std::string("box2"), 5, 5, 1, BLANK },
        { std::string("box2"), 6, 6, 1, VERTICAL_EDGE },
        { std::string("box1"), 0, 0, 2, VERTICAL_EDGE },
        { std::string("box1"), 1, 1, 2, BLANK },
        { std::string("box2"), 2, 2, 2, VERTICAL_EDGE },
        { std::string("box2"), 3, 3, 2, BLANK },
        { std::string("box2"), 4, 4, 2, VERTICAL_EDGE },
        { std::string("box2"), 5, 5, 2, BLANK },
        { std::string("box2"), 6, 6, 2, VERTICAL_EDGE },
        { std::string("box1"), 0, 0, 3, VERTICAL_EDGE },
        { std::string("box1"), 1, 1, 3, BLANK },
        { std::string("box2"), 2, 2, 3, CORNER },
        { std::string("box2"), 3, 3, 3, HORIZONTAL_EDGE },
        { std::string("box2"), 4, 4, 3, CORNER },
        { std::string("box2"), 5, 5, 3, BLANK },
        { std::string("box2"), 6, 6, 3, VERTICAL_EDGE },

        { std::string("box1"), 0, 0, 4, CORNER },
        { std::string("box1"), 1, 5, 4, HORIZONTAL_EDGE },
        { std::string("box1"), 6, 6, 4, CORNER }
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
            curX++;
        } else {
            i++;
        }
    }
    std::cout << "\n";
}