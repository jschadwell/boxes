#ifndef ABSTRACT_BOX_VISITOR_H
#define ABSTRACT_BOX_VISITOR_H

class Box;

class AbstractBoxVisitor {
public:
    AbstractBoxVisitor() = default;
    virtual ~AbstractBoxVisitor() = default;

    virtual void visitBox(Box* box) = 0;
};

#endif