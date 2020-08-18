#ifndef BOX_CONFIG_PARSER_H
#define BOX_CONFIG_PARSER_H

#include "toml.hpp"
#include <map>
#include <vector>

using BoxConfiguration = std::map<std::string, std::vector<std::string> >;

class BoxConfigParser {
public:
    BoxConfigParser() = default;
    ~BoxConfigParser() = default;

    BoxConfiguration* parse(char* configFile);

private:
    toml::table _tomlConfig;
    BoxConfiguration _boxConfig;
};

#endif // BOX_CONFIG_WRAPPER_H