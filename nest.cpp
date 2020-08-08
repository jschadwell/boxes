#include "NestedBoxBuilder.h"
#include "Box.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    // Check the command line arguments
    if (argc != 2) {
        // Display usage message and exit
        std::cerr << "Usage: " << argv[0] << " config_file" << std::endl;
        return 1;
    }

    std::string configFile(argv[1]);

    NestedBoxBuilder builder;
    if (!builder.load(configFile)) {
        return 1;
    }

    if (!builder.buildNestedBox()) {
        return 1;
    }

    std::cout << "Input file: " << argv[1] << std::endl;

    Box box;

    box.print();
}