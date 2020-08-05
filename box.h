#ifndef BOX_H
#define BOX_H

#include <vector>

class Box {
public:
	Box();
	~Box();

//	void addChild(Box* child);
//	int numChildren();
	void print();

private:
	std::vector<std::unique_ptr<Box> > _children;
};

#endif // BOX_H