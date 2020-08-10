#include "BoxConfiguration.h"
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

    BoxConfiguration boxConfiguration;

    if (!boxConfiguration.init(configFile)) {
        return 1;
    }

    return 0;
}