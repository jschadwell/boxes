#include "BoxConfigurator.h"
#include "BoxConfiguration.h"
#include "BoxRepository.h"
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
        auto children = item->getChildren();
        for (auto childIter = begin(children); childIter != end(children); childIter++) {
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

    return 0;
}