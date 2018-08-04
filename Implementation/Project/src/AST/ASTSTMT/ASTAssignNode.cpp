#include "ASTAssignNode.h"
#include "../ASTEXPR/ASTIdentifierNode.h"

namespace AST {

    ASTAssignNode::ASTAssignNode(const std::string &identifier, const ASTExprNode *expr) :
        identifier(new ASTIdentifierNode(identifier)), expr(expr) {}

    const ASTIdentifierNode *ASTAssignNode::getIdentifier() const {
        return identifier;
    }

    const ASTExprNode *ASTAssignNode::getExpr() const {
        return expr;
    }

    void ASTAssignNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTAssignNode::~ASTAssignNode(void) {
        delete identifier;
        delete expr;
    }
}