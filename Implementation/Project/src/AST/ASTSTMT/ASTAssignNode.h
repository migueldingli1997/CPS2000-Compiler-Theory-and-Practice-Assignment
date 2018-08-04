#ifndef CPS2000_ASTASSIGNNODE_H
#define CPS2000_ASTASSIGNNODE_H

#include "../ASTStmtNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTExprNode;

    class ASTAssignNode final : public ASTStmtNode {

    public:
        ASTAssignNode(const std::string &identifier, const ASTExprNode *expr);

        const ASTIdentifierNode *getIdentifier() const;

        const ASTExprNode *getExpr() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTAssignNode(void);

    private:
        const ASTIdentifierNode *identifier;
        const ASTExprNode *expr;
    };
}

#endif //CPS2000_ASTASSIGNNODE_H
