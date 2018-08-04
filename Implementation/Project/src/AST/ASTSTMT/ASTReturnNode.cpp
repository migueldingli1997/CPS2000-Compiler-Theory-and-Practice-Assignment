#include "ASTReturnNode.h"
#include "../ASTExprNode.h"

namespace AST {

    ASTReturnNode::ASTReturnNode(const ASTExprNode *expr) : expr(expr) {}

    const ASTExprNode *ASTReturnNode::getExpr() const {
        return expr;
    }

    void ASTReturnNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTReturnNode::~ASTReturnNode(void) {
        delete expr;
    }
}