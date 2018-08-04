#ifndef CPS2000_ASTIDENTIFIERNODE_H
#define CPS2000_ASTIDENTIFIERNODE_H

#include "../ASTExprNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTIdentifierNode final : public ASTExprNode {

    public:
        ASTIdentifierNode(const std::string &identifier);

        const std::string &getStr() const;

        void Accept(VST::Visitor *v) const override;

    private:
        const std::string identifier;
    };
}

#endif //CPS2000_ASTIDENTIFIERNODE_H
