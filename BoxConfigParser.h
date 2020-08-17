#ifndef BOX_CONFIG_WRAPPER_H
#define BOX_CONFIG_WRAPPER_H

#include "pugixml.hpp"
#include <string>

class BoxConfigWrapper {
public:
    BoxConfigWrapper(std::string configFile);
    ~BoxConfigWrapper() = default;

    bool init();

private:
    bool loadConfig();
    bool validateConfig();
    std::string _configFile;
    pugi::xml_document _configDoc;
};

#endif // BOX_CONFIG_WRAPPER_H