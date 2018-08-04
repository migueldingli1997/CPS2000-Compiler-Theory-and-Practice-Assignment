#ifndef CPS2000_ASTINTNODE_H
#define CPS2000_ASTINTNODE_H

#include "../ASTExprNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTIntNode final : public ASTExprNode {

    public:
        ASTIntNode(const int value);

        const int getValue() const;

        void Accept(VST::Visitor *v) const override;

    private:
        const int value;
    };
}

#endif //CPS2000_ASTINTNODE_H
