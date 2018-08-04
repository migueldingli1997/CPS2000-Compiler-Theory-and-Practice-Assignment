#ifndef CPS2000_ASTSUBEXPRNODE_H
#define CPS2000_ASTSUBEXPRNODE_H

#include "../ASTExprNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTSubExprNode final : public ASTExprNode {

    public:
        ASTSubExprNode(const ASTExprNode *expr);

        const ASTExprNode *getExpr() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTSubExprNode(void);

    private:
        const ASTExprNode *expr;
    };
}

#endif //CPS2000_ASTSUBEXPRNODE_H
