#ifndef BOX_H
#define BOX_H

#include "AbstractBoxVisitor.h"
#include <vector>
#include <string>

class Box;
using BoxUPtr = std::unique_ptr<Box>;
using BoxIter = std::vector<BoxUPtr>::iterator;

enum class Orientation { horizontal, vertical };

class Box {
public:
    Box(std::string name);
    ~Box() = default;

    std::string& getName();
    BoxIter begin();
    BoxIter end();
    void addChild(Box* child);
    bool hasChildren();
    void accept(AbstractBoxVisitor& visitor);

private:
    std::string _name;
    std::vector<BoxUPtr> _children;
};

#endif // BOX_H