#include "Box.h"
#include "DebugPrintVisitor.h"
#include "ReorganizeBoxVisitor.h"
#include "BoxConfigParser.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // Check the command line arguments
    if (argc != 2) {
        // Display usage message and exit
        std::cerr << "Usage: " << argv[0] << " config_file" << std::endl;
        return 1;
    }

    // Parse the box configuration file
    BoxConfigParser configParser;
    BoxUPtr topBox = configParser.parse(argv[1]);
    if (!topBox) {
        return 1;
    }

    ReorganizeBoxVisitor reorganizer;
    topBox->accept(reorganizer);

    DebugPrintVisitor d;
    topBox->accept(d);

    return 0;
}