#ifndef CPS2000_ASTACTUALPARAMSNODE_H
#define CPS2000_ASTACTUALPARAMSNODE_H

#include <vector>
#include "../ASTNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTExprNode;

    class ASTActualParamsNode final : public ASTNode {

    public:
        ASTActualParamsNode(const std::vector<const ASTExprNode *> &params);

        const std::vector<const ASTExprNode *> &getParams() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTActualParamsNode(void);

    private:
        const std::vector<const ASTExprNode *> params;
    };
}

#endif //CPS2000_ASTACTUALPARAMSNODE_H
