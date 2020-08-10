#ifndef BOX_H
#define BOX_H

#include <set>
#include <string>

class Box {
public:
    Box(std::string id);
    ~Box() = default;

    bool addChild(std::string id);
    void print();

private:
	std::string _id;
	std::set<std::string> _children;
};

#endif // BOX_H