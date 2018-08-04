#ifndef CPS2000_ASTPRINTNODE_H
#define CPS2000_ASTPRINTNODE_H

#include "../ASTStmtNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTExprNode;

    class ASTPrintNode final : public ASTStmtNode {

    public:
        ASTPrintNode(const ASTExprNode *expr);

        const ASTExprNode *getExpr() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTPrintNode(void);

    private:
        const ASTExprNode *expr;
    };
}

#endif //CPS2000_ASTPRINTNODE_H
