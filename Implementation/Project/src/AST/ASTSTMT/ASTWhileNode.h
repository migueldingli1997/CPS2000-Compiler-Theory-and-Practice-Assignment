#ifndef CPS2000_ASTWHILENODE_H
#define CPS2000_ASTWHILENODE_H

#include "../ASTStmtNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTExprNode;

    class ASTBlockNode;

    class ASTWhileNode final : public ASTStmtNode {

    public:
        ASTWhileNode(const ASTExprNode *expr, const ASTBlockNode *block);

        const ASTExprNode *getExpr() const;

        const ASTBlockNode *getBlock() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTWhileNode(void);

    private:
        const ASTExprNode *expr;
        const ASTBlockNode *block;
    };
}

#endif //CPS2000_ASTWHILENODE_H
