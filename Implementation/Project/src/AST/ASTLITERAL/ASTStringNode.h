#ifndef CPS2000_ASTSTRINGNODE_H
#define CPS2000_ASTSTRINGNODE_H

#include <string>
#include "../ASTExprNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTStringNode final : public ASTExprNode {

    public:
        ASTStringNode(const std::string &value);

        const std::string &getValue() const;

        void Accept(VST::Visitor *v) const override;

    private:
        const std::string value;
    };
}

#endif //CPS2000_ASTSTRINGNODE_H
