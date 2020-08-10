#ifndef BOX_CONFIGURATION_H
#define BOX_CONFIGURATION_H

#include "Box.h"
#include <boost/property_tree/xml_parser.hpp>
#include <string>
#include <map>
#include <exception>

namespace pt = boost::property_tree;


class BoxConfiguration {
public:
    BoxConfiguration();
    ~BoxConfiguration();

    bool init(std::string& xmlFile);

private:
    bool loadConfigFile(std::string& xmlFile);
    bool readConfig();
    bool validateConfig();
    void errorMsg(const char* msg);

    pt::ptree _tree;
    std::map<std::string, std::unique_ptr<Box> > _boxMap;
};

#endif // BOX_CONFIGURATION_H