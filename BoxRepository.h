#ifndef BOX_REPOSITORY_H
#define BOX_REPOSITORY_H

#include "Box.h"
#include <map>
#include <string>

class BoxRepository {
public:
    BoxRepository() = default;
    ~BoxRepository() = default;

    void addBox(std::string id);
    Box* getBox(std::string id);

private:
    std::map<std::string, BoxPtr> _boxMap;
};

#endif