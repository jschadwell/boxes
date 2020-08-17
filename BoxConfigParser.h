#ifndef BOX_CONFIG_PARSER_H
#define BOX_CONFIG_PARSER_H

#include "pugixml.hpp"
#include <string>

class BoxConfigParser {
public:
    BoxConfigParser() = default;
    ~BoxConfigParser() = default;

    bool parse(char* configFile);

private:
    bool loadConfig(char* configFile);
    bool validateConfig();
    pugi::xml_document _configDoc;
};

#endif // BOX_CONFIG_WRAPPER_H