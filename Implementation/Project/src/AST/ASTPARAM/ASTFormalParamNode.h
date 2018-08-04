#ifndef CPS2000_ASTFORMALPARAMNODE_H
#define CPS2000_ASTFORMALPARAMNODE_H

#include <string>
#include "../ASTNode.h"
#include "../../General/Type.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTFormalParamNode final : public ASTNode {

    public:
        ASTFormalParamNode(const std::string &identifier, const Type &type);

        const ASTIdentifierNode *getIdentifier() const;

        const Type &getType() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTFormalParamNode(void);

    private:
        const ASTIdentifierNode *identifier;
        const Type type;
    };
}

#endif //CPS2000_ASTFORMALPARAMNODE_H
