#ifndef DEBUG_PRINT_VISITOR_H
#define DEBUG_PRINT_VISITOR_H

#include "AbstractBoxVisitor.h"

class DebugPrintVisitor : public AbstractBoxVisitor {
public:
    DebugPrintVisitor() = default;
    virtual ~DebugPrintVisitor() = default;

    void visitBox(Box* Box) override;
};

#endif