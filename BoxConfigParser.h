#ifndef BOX_CONFIG_PARSER_H
#define BOX_CONFIG_PARSER_H

#include "toml.hpp"
#include <string>
#include <map>

using BoxChildren = std::vector<std::string>;
using BoxChildrenUPtr = std::unique_ptr<BoxChildren>;
using BoxName = std::string;
using BoxConfigMap = std::map<BoxName, BoxChildrenUPtr>;

class BoxConfigParser {
public:
    BoxConfigParser() = default;
    ~BoxConfigParser() = default;

    bool parse(char* configFile, BoxConfigMap& boxConfig);

private:
	bool parseBoxNames(BoxConfigMap& boxConfig);
	bool parseBoxChildren(BoxConfigMap& boxConfig);
    toml::table _tomlConfig;
    BoxConfigMap _boxes;
};

#endif // BOX_CONFIG_WRAPPER_H