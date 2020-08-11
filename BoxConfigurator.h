#ifndef BOX_CONFIGURATOR_H
#define BOX_CONFIGURATOR_H

#include "BoxConfiguration.h"
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <exception>

namespace pt = boost::property_tree;

class BoxConfigurator {
public:
    BoxConfigurator();
    ~BoxConfigurator();

    bool loadConfig(std::string& xmlFile, std::vector<BoxConfigurationPtr>& configList);

private:
    bool readConfigFile(std::string& xmlFile);
    bool parseConfig(std::vector<BoxConfigurationPtr>& configList);
    bool validateConfig(std::vector<BoxConfigurationPtr>& configList);
    void errorMsg(const std::string& msg);
    void errorMsg(const char* msg);

    pt::ptree _tree;
};

#endif // BOX_CONFIGURATOR_H