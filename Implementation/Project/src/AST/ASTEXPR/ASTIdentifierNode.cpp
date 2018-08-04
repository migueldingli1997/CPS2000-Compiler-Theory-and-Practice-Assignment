#include "ASTIdentifierNode.h"

AST::ASTIdentifierNode::ASTIdentifierNode(const std::string &identifier) : identifier(identifier) {}

const std::string &AST::ASTIdentifierNode::getStr() const {
    return identifier;
}

void AST::ASTIdentifierNode::Accept(VST::Visitor *v) const {
    v->visit(this);
}
