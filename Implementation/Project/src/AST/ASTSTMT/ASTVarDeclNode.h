#ifndef CPS2000_ASTVARDECLNODE_H
#define CPS2000_ASTVARDECLNODE_H

#include "../ASTStmtNode.h"
#include "../../General/Type.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTExprNode;

    class ASTVarDeclNode final : public ASTStmtNode {

    public:
        ASTVarDeclNode(const std::string &identifier, const Type &type, const ASTExprNode *expr);

        const ASTIdentifierNode *getIdentifier() const;

        const Type &getType() const;

        const ASTExprNode *getExpr() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTVarDeclNode(void);

    private:
        const ASTIdentifierNode *identifier;
        const Type type;
        const ASTExprNode *expr;
    };
}

#endif //CPS2000_ASTVARDECLNODE_H
