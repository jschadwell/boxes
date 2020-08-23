#ifndef PRETTY_PRINT_VISITOR_H
#define PRETTY_PRINT_VISITOR_H

#include "AbstractBoxVisitor.h"
#include <string>
#include <vector>

class PrettyPrintVisitor : public AbstractBoxVisitor {
public:
    PrettyPrintVisitor() = default;
    virtual ~PrettyPrintVisitor() = default;

    void visitBox(Box* Box) override;

private:
    struct PrintInstruction {
        std::string boxName;
        int startX;
        int endX;
        char ch;
    };
    std::vector<std::unique_ptr<PrintInstruction> > _instructions;
};

#endif