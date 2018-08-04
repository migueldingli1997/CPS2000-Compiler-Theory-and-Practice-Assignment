#include "ASTPrintNode.h"
#include "../ASTExprNode.h"

namespace AST {

    ASTPrintNode::ASTPrintNode(const ASTExprNode *expr) : expr(expr) {}

    const ASTExprNode *ASTPrintNode::getExpr() const {
        return expr;
    }

    void ASTPrintNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTPrintNode::~ASTPrintNode(void) {
        delete expr;
    }
}