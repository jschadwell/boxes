#ifndef REORGANIZE_BOX_VISITOR_H
#define REORGANIZE_BOX_VISITOR_H

#include "AbstractBoxVisitor.h"

class ReorganizeBoxVisitor : public AbstractBoxVisitor {
public:
    ReorganizeBoxVisitor() = default;
    virtual ~ReorganizeBoxVisitor() = default;

    void visitBox(Box* box) override;
};

#endif