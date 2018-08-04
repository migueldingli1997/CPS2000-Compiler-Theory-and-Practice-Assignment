#include "ASTIfNode.h"
#include "../ASTExprNode.h"
#include "ASTBlockNode.h"

namespace AST {

    ASTIfNode::ASTIfNode(const ASTExprNode *expr, const ASTBlockNode *ifBlock, const ASTBlockNode *elseBlock) :
            expr(expr), ifBlock(ifBlock), elseBlock(elseBlock) {}

    const ASTExprNode *ASTIfNode::getExpr() const {
        return expr;
    }

    const ASTBlockNode *ASTIfNode::getIfBlock() const {
        return ifBlock;
    }

    const ASTBlockNode *ASTIfNode::getElseBlock() const {
        return elseBlock;
    }

    void ASTIfNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTIfNode::~ASTIfNode(void) {
        delete expr;
        delete ifBlock;
        if (elseBlock != nullptr) delete elseBlock;
    }
}
