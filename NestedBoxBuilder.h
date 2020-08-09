#ifndef NESTED_BOX_BUILDER_H
#define NESTED_BOX_BUILDER_H

#include "Box.h"
#include <boost/property_tree/ptree.hpp>
#include <exception>
#include <string>
#include <map>

namespace pt = boost::property_tree;

class NestedBoxBuilder {
public:
    NestedBoxBuilder();
    ~NestedBoxBuilder();

    bool loadConfigFile(std::string& xmlFile);
    bool buildNestedBox();
    bool parseConfigFile();
    bool parseParents();
    Box* getNestedBox();

private:
    void errorMsg(const std::exception& e);

    pt::ptree _tree;

    std::map<std::string, std::unique_ptr<Box> > _boxMap;
};

#endif // NESTED_BOX_BUILDER_H