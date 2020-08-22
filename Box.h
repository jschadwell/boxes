#ifndef BOX_H
#define BOX_H

#include "AbstractBoxVisitor.h"
#include <vector>
#include <string>

class Box;
using BoxUPtr = std::unique_ptr<Box>;
using BoxIter = std::vector<BoxUPtr>::iterator;

class Box {
public:
    enum class Orientation { horizontal, vertical };

    Box(std::string name);
    ~Box() = default;

    std::string& getName();
    void setWidth(int w);
    int getWidth();
    void setHeight(int h);
    int getHeight();
    void setOrientation(Orientation o);
    Orientation getOrientation();
    BoxIter begin();
    BoxIter end();
    void addChild(Box* child);
    bool hasChildren();
    void accept(AbstractBoxVisitor& visitor);

private:
    std::string _name;
    std::vector<BoxUPtr> _children;
    int _width;
    int _height;
    Orientation _orientation;
};

#endif // BOX_H