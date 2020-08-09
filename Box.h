#ifndef BOX_H
#define BOX_H

#include <vector>
#include <string>

class Box {
public:
    Box(std::string id);
    ~Box();

//    void addChild(Box* child);
//    int numChildren();
    void print();

private:
	std::string _id;
    //std::vector<Box*> _children;
};

#endif // BOX_H