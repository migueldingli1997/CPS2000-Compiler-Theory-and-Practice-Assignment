#include "ASTRealNode.h"

namespace AST {
    ASTRealNode::ASTRealNode(const double value) : value(value) {}

    const double ASTRealNode::getValue() const {
        return value;
    }

    void ASTRealNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }
}