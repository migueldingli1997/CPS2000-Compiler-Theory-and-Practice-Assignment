#ifndef CPS2000_ASTFORMALPARAMSNODE_H
#define CPS2000_ASTFORMALPARAMSNODE_H

#include <vector>
#include "../ASTNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTFormalParamNode;

    class ASTFormalParamsNode final : public ASTNode {

    public:
        ASTFormalParamsNode(const std::vector<const ASTFormalParamNode *> &params);

        const std::vector<const ASTFormalParamNode *> &getParams() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTFormalParamsNode(void);

    private:
        const std::vector<const ASTFormalParamNode *> params;
    };
}

#endif //CPS2000_ASTFORMALPARAMSNODE_H
