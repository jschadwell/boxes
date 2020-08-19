#include "BoxRepository.h"
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
    BoxConfigMap boxConfig;
    if (!configParser.parse(argv[1], boxConfig)) {
        return 1;
    }

    for (auto&& box : boxConfig) {
        std::cout << "Box = " << box.first << "\n";
        for (auto&& child : *(box.second)) {
            std::cout << "    Child = " << child << "\n";
        }
    }

#if 0
    // Get configuration from config file
    BoxConfigurator boxConfigurator;
    std::vector<BoxConfigurationPtr> boxConfig;
    if (!boxConfigurator.loadConfig(configFile, boxConfig)) {
        return 1;
    }

    // Create boxes
    BoxRepository boxRepository;
    for (auto&& item : boxConfig) {
        boxRepository.addBox(item->getId());
    }

    // Set up parent/child relationships in boxes
    for (auto&& item : boxConfig) {
        for (auto childIter = (*item).begin(); childIter != (*item).end(); childIter++) {
            auto parent = boxRepository.getBox(item->getId());
            auto child = boxRepository.getBox(*childIter);
            parent->addChild(child);
            child->addParent(parent);
        }
    }

    // Find top-level box
    Box* top = nullptr;
    for (auto&& item : boxConfig) {
        if (!boxRepository.getBox(item->getId())->getParent()) {
            top = boxRepository.getBox(item->getId());
            break;
        }
    }

    top->print();
    top->resize();
    top->print();

#endif
    return 0;
}