#ifndef BOX_CONFIGURATOR_H
#define BOX_CONFIGURATOR_H

#include "Box.h"
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <map>
#include <exception>

namespace pt = boost::property_tree;


class BoxConfigurator {
public:
    BoxConfigurator();
    ~BoxConfigurator();

    bool loadConfig(std::string& xmlFile);

private:
    bool readConfigFile(std::string& xmlFile);
    bool parseConfig();
    bool validateConfig();
    void errorMsg(const char* msg);

    pt::ptree _tree;
    std::map<std::string, std::unique_ptr<Box> > _boxMap;
};

#endif // BOX_CONFIGURATOR_H