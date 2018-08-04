#ifndef CPS2000_ASTFUNCCALLNODE_H
#define CPS2000_ASTFUNCCALLNODE_H

#include "../ASTExprNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTActualParamsNode;

    class ASTFuncCallNode final : public ASTExprNode {

    public:
        ASTFuncCallNode(const std::string identifier, const ASTActualParamsNode *params);

        const ASTIdentifierNode *getIdentifier() const;

        const ASTActualParamsNode *getParams() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTFuncCallNode(void);

    private:
        const ASTIdentifierNode *identifier;
        const ASTActualParamsNode *params;
    };
}

#endif //CPS2000_ASTFUNCCALLNODE_H
