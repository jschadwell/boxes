#ifndef NESTED_BOX_BUILDER_H
#define NESTED_BOX_BUILDER_H

#include "Box.h"
#include <boost/property_tree/ptree.hpp>
#include <exception>
#include <string>

namespace pt = boost::property_tree;

class NestedBoxBuilder {
public:
    NestedBoxBuilder();
    ~NestedBoxBuilder();

    bool load(std::string& xmlFile);
    bool buildNestedBox();
    Box* getNestedBox();

private:
    void errorMsg(const std::exception& e);

    pt::ptree _tree;
};

#endif // NESTED_BOX_BUILDER_H