#ifndef BOX_CONFIG_PARSER_H
#define BOX_CONFIG_PARSER_H

#include "toml.hpp"

class BoxConfigParser {
public:
    BoxConfigParser() = default;
    ~BoxConfigParser() = default;

    bool parse(char* configFile);

private:
    toml::table _tomlConfig;
};

#endif // BOX_CONFIG_WRAPPER_H