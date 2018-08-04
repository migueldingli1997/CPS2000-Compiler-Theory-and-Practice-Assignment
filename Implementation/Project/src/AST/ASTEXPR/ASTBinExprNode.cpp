#include "ASTBinExprNode.h"

namespace AST {

    ASTBinExprNode::ASTBinExprNode(const ASTExprNode *expr1, const ASTExprNode *expr2, const std::string &op) :
        expr1(expr1), expr2(expr2), op(op) {}

    const ASTExprNode *ASTBinExprNode::getExpr1() const {
        return expr1;
    }

    const ASTExprNode *ASTBinExprNode::getExpr2() const {
        return expr2;
    }

    const std::string &ASTBinExprNode::getOp() const {
        return op;
    }

    void ASTBinExprNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTBinExprNode::~ASTBinExprNode(void) {
        delete expr1;
        delete expr2;
    }
}
