#ifndef BOX_CONFIG_PARSER_H
#define BOX_CONFIG_PARSER_H

#include "toml.hpp"
#include "Box.h"
#include <string>
#include <map>

class BoxConfigParser {
public:
    BoxConfigParser() = default;
    ~BoxConfigParser() = default;

    BoxUPtr parse(char* configFile);

private:
	bool parseBoxNames();
	bool parseBoxChildren();
	Box* getMainBox();
    toml::table _tomlConfig;
    std::map<std::string, Box*> _boxMap;
};

#endif // BOX_CONFIG_WRAPPER_H