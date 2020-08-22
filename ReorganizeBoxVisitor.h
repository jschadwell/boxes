#ifndef REORGANIZE_BOX_VISITOR_H
#define REORGANIZE_BOX_VISITOR_H

#include "AbstractBoxVisitor.h"
#include <map>

class ReorganizeBoxVisitor : public AbstractBoxVisitor {
public:
    ReorganizeBoxVisitor() = default;
    virtual ~ReorganizeBoxVisitor() = default;

    void visitBox(Box* box) override;

private:
    void makeHorizontalStack(Box* box, int& width, int& height);
    void makeVerticalStack(Box* box, int& width, int& height);

    struct BoxParm {
        BoxParm(int w, int h) : width(w), height(h) {}
        ~BoxParm() = default;

        int width;
        int height;
    };
};

#endif