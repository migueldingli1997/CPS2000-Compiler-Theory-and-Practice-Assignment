#include "ASTIntNode.h"

namespace AST {
    ASTIntNode::ASTIntNode(const int value) : value(value) {}

    const int ASTIntNode::getValue() const {
        return value;
    }

    void ASTIntNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }
}
