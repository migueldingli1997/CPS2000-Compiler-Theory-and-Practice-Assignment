#include "ASTSubExprNode.h"

namespace AST {

    ASTSubExprNode::ASTSubExprNode(const ASTExprNode *expr) : expr(expr) {}

    const ASTExprNode *ASTSubExprNode::getExpr() const {
        return expr;
    }

    void ASTSubExprNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTSubExprNode::~ASTSubExprNode(void) {
        delete expr;
    }
}