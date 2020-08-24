#ifndef BOX_H
#define BOX_H

#include "AbstractBoxVisitor.h"
#include <vector>
#include <string>

class Box;
using BoxUPtr = std::unique_ptr<Box>;
using BoxIter = std::vector<BoxUPtr>::iterator;
using BoxReverseIter = std::vector<BoxUPtr>::reverse_iterator;

class Box {
public:
    static const int MIN_WIDTH = 3;
    static const int MIN_HEIGHT = 3;

    enum class Orientation { horizontal, vertical };

    Box(std::string name, Orientation o);
    ~Box() = default;

    std::string& getName();
    void setParent(Box* box);
    Box* getParent();
    void setX(int x);
    int getX();
    void setY(int y);
    int getY();
    void setWidth(int w);
    int getWidth();
    void setHeight(int h);
    int getHeight();
    void setOrientation(Orientation o);
    Orientation getOrientation();
    BoxIter begin();
    BoxIter end();
    BoxReverseIter rbegin();
    BoxReverseIter rend();
    void addChild(Box* child);
    Box* getChild(std::string& name);
    bool hasChild(std::string& name);
    bool hasChildren();
    bool isSiblingOf(std::string& name);
    void accept(AbstractBoxVisitor& visitor);

private:
    std::string _name;
    Box* _parent;
    std::vector<BoxUPtr> _children;
    int _x;
    int _y;
    int _width;
    int _height;
    Orientation _orientation;
};

#endif // BOX_H