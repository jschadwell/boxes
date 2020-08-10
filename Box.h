#ifndef BOX_H
#define BOX_H

#include <set>
#include <string>

using ChildSet = std::set<std::string>;

class Box {
public:
    Box(std::string id);
    ~Box() = default;

    bool addChild(std::string id);
    const ChildSet& getChildren() const;
    void print();

private:
	std::string _id;
	ChildSet _children;
};

#endif // BOX_H