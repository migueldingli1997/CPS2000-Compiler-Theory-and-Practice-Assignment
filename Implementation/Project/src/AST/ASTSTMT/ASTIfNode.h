#ifndef CPS2000_ASTIFNODE_H
#define CPS2000_ASTIFNODE_H

#include "../ASTStmtNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTExprNode;

    class ASTBlockNode;

    class ASTIfNode final : public ASTStmtNode {

    public:
        ASTIfNode(const ASTExprNode *expr, const ASTBlockNode *ifBlock, const ASTBlockNode *elseBlock);

        const ASTExprNode *getExpr() const;

        const ASTBlockNode *getIfBlock() const;

        const ASTBlockNode *getElseBlock() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTIfNode(void);

    private:
        const ASTExprNode *expr;
        const ASTBlockNode *ifBlock;
        const ASTBlockNode *elseBlock;
    };
}

#endif //CPS2000_ASTIFNODE_H
