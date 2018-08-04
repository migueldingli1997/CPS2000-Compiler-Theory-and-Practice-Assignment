#ifndef CPS2000_ASTEXPRNODE_H
#define CPS2000_ASTEXPRNODE_H

#include "ASTNode.h"

namespace AST {

    class ASTExprNode : public ASTNode {

    public:
        virtual void Accept(VST::Visitor *v) const override = 0;

        virtual ~ASTExprNode(void) {}
    };
}

#endif //CPS2000_ASTEXPRNODE_H
