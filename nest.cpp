#include "BoxConfigurator.h"
#include "BoxConfiguration.h"
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

    BoxConfigurator boxConfigurator;
    BoxConfigList boxConfig;

    if (!boxConfigurator.loadConfig(configFile, boxConfig)) {
        return 1;
    }

    for (auto&& item : boxConfig) {
        item->print();
    }

    return 0;
}