#ifndef BOX_CONFIGURATOR_H
#define BOX_CONFIGURATOR_H

#include "BoxConfiguration.h"
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <map>
#include <exception>

namespace pt = boost::property_tree;

using BoxConfigList = std::vector<std::unique_ptr<BoxConfiguration> >;

class BoxConfigurator {
public:
    BoxConfigurator();
    ~BoxConfigurator();

    bool loadConfig(std::string& xmlFile, BoxConfigList& configList);

private:
    bool readConfigFile(std::string& xmlFile);
    bool parseConfig(BoxConfigList& configList);
    bool validateConfig(BoxConfigList& configList);
    void errorMsg(const char* msg);

    pt::ptree _tree;
};

#endif // BOX_CONFIGURATOR_H