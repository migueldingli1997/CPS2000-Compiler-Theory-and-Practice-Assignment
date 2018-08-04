#include "ASTVarDeclNode.h"
#include "../ASTEXPR/ASTIdentifierNode.h"

namespace AST {

    ASTVarDeclNode::ASTVarDeclNode(const std::string &identifier, const Type &type, const ASTExprNode *expr)
        : identifier(new AST::ASTIdentifierNode(identifier)), type(type), expr(expr) {}

    const ASTIdentifierNode *ASTVarDeclNode::getIdentifier() const {
        return identifier;
    }

    const Type &ASTVarDeclNode::getType() const {
        return type;
    }

    const ASTExprNode *ASTVarDeclNode::getExpr() const {
        return expr;
    }

    void ASTVarDeclNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTVarDeclNode::~ASTVarDeclNode(void) {
        delete identifier;
        delete expr;
    }
}