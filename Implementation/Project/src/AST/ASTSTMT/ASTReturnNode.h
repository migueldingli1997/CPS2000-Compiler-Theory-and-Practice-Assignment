#ifndef CPS2000_ASTRETURNNODE_H
#define CPS2000_ASTRETURNNODE_H

#include "../ASTStmtNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTExprNode;

    class ASTReturnNode final : public ASTStmtNode {

    public:
        ASTReturnNode(const ASTExprNode *expr);

        const ASTExprNode *getExpr() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTReturnNode(void);

    private:
        const ASTExprNode *expr;
    };
}

#endif //CPS2000_ASTRETURNNODE_H
