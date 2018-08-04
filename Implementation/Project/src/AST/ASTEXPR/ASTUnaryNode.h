#ifndef CPS2000_ASTUNARYNODE_H
#define CPS2000_ASTUNARYNODE_H

#include "../ASTExprNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTUnaryNode final : public ASTExprNode {

    public:
        ASTUnaryNode(const std::string &op, const ASTExprNode *expr);

        const std::string &getOp() const;

        const ASTExprNode *getExpr() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTUnaryNode(void);

    private:
        const std::string op;
        const ASTExprNode *expr;
    };
}

#endif //CPS2000_ASTUNARYNODE_H
