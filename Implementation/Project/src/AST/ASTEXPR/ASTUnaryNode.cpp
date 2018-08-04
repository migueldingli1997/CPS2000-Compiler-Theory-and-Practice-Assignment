#include "ASTUnaryNode.h"

namespace AST {

    ASTUnaryNode::ASTUnaryNode(const std::string &op, const ASTExprNode *expr) : op(op), expr(expr) {}

    const std::string &ASTUnaryNode::getOp() const {
        return op;
    }

    const ASTExprNode *ASTUnaryNode::getExpr() const {
        return expr;
    }

    void ASTUnaryNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTUnaryNode::~ASTUnaryNode(void) {
        delete expr;
    }
}