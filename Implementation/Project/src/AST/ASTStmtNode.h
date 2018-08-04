#ifndef CPS2000_ASTSTATEMENTNODE_H
#define CPS2000_ASTSTATEMENTNODE_H

#include "ASTNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTStmtNode : public ASTNode {

    public:
        virtual void Accept(VST::Visitor *v) const override = 0;

        virtual ~ASTStmtNode(void) {}
    };
}

#endif //CPS2000_ASTSTATEMENTNODE_H
