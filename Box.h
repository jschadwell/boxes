#ifndef BOX_H
#define BOX_H

#include <vector>

class Box;
using BoxPtr = std::unique_ptr<Box>;

class Box {
public:
    Box();
    ~Box() = default;

    void addParent(Box* parent);
    void addChild(Box* child);

private:
    Box* _parent;
    std::vector<Box*> _children;
};

#endif // BOX_H