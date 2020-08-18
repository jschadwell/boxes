#ifndef BOX_CONFIG_PARSER_H
#define BOX_CONFIG_PARSER_H

#include "toml.hpp"
#include <string>

class BoxConfigParser {
public:
    BoxConfigParser() = default;
    ~BoxConfigParser() = default;

    bool parse(char* configFile);

private:
    bool loadConfig(char* configFile);
    bool validateConfig();
    toml::table _config;
};

#endif // BOX_CONFIG_WRAPPER_H