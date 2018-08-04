#ifndef CPS2000_ASTREALNODE_H
#define CPS2000_ASTREALNODE_H

#include "../ASTExprNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTRealNode final : public ASTExprNode {

    public:
        ASTRealNode(const double value);

        const double getValue() const;

        void Accept(VST::Visitor *v) const override;

    private:
        const double value;
    };
}

#endif //CPS2000_ASTREALNODE_H
