#include "ASTBoolNode.h"

namespace AST {
    ASTBoolNode::ASTBoolNode(const bool value) : value(value) {}

    const bool ASTBoolNode::getValue() const {
        return value;
    }

    void ASTBoolNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }
}