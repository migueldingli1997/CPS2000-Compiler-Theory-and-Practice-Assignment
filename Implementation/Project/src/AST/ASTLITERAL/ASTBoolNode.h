#ifndef CPS2000_ASTBOOLNODE_H
#define CPS2000_ASTBOOLNODE_H

#include "../ASTExprNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTBoolNode final : public ASTExprNode {

    public:
        ASTBoolNode(const bool value);

        const bool getValue() const;

        void Accept(VST::Visitor *v) const override;

    private:
        const bool value;
    };
}

#endif //CPS2000_ASTBOOLNODE_H
