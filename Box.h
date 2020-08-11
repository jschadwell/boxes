#ifndef BOX_H
#define BOX_H

#include <vector>
#include <string>

class Box;
using BoxPtr = std::unique_ptr<Box>;

enum class Orientation { horizontal, vertical };

class Box {
public:
    Box(std::string id);
    ~Box() = default;

    void addParent(Box* parent);
    Box* getParent();
    void addChild(Box* child);
    std::vector<Box*>& getChildren();
    void setWidth(int w);
    int getWidth();
    void setHeight(int h);
    int getHeight();
    void setOrientation(Orientation o);
    Orientation getOrientation();
    void resize();
    void print();

private:
    std::string _id;
    int _width;
    int _height;
    Orientation _orientation;
    Box* _parent;
    std::vector<Box*> _children;
};

#endif // BOX_H