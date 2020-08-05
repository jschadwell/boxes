#include "box.h"
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>

namespace filesys = boost::filesystem;

int main(int argc, char* argv[]) {
    // Check the command line arguments
    if (argc != 2) {
        // Display usage message and exit
        std::cerr << "Usage: " << argv[0] << " config_file" << std::endl;
        return 1;
    }

    try {
        // Check to make sure the input file exists
        filesys::path filepath(argv[1]);
        if (!filesys::exists(filepath)) {
            std::cerr << argv[0] << ": " << argv[1] << ": No such file" << std::endl;
            return 1;
        }
        // Check to make sure the input file is the correct type
        if (!filesys::is_regular_file(filepath)) {
            std::cerr << argv[0] << ": " << argv[1] << ": Invalid file type" << std::endl;
            return 1;
        }
    } catch (filesys::filesystem_error& e) {
        // Something bad happened
        std::cerr << e.what() << std::endl;
        return 1;
    }

    std::cout << "Input file: " << argv[1] << std::endl;

    Box box;

    box.print();
}