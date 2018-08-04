#include "ASTStringNode.h"

namespace AST {
    ASTStringNode::ASTStringNode(const std::string &value) : value(value) {}

    const std::string &ASTStringNode::getValue() const {
        return value;
    }

    void ASTStringNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }
}