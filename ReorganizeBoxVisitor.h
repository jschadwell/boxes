#ifndef REORGANIZE_BOX_VISITOR_H
#define REORGANIZE_BOX_VISITOR_H

#include "AbstractBoxVisitor.h"
#include "Box.h"
#include <map>

class ReorganizeBoxVisitor : public AbstractBoxVisitor {
public:
    ReorganizeBoxVisitor() = default;
    virtual ~ReorganizeBoxVisitor() = default;

    void visitBox(Box* box) override;

private:
    void makeHorizontalStack(Box* box, int& width, int& height);
    void makeVerticalStack(Box* box, int& width, int& height);
    void repositionChildrenHorizontally(Box* box);
    void repositionChildrenVertically(Box* box);
    void repositionChildrenInBox(Box* box);

    std::vector<Box*> _visited;
};

#endif