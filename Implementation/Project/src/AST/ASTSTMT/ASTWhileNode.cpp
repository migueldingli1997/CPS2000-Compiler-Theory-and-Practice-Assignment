#include "ASTWhileNode.h"
#include "../ASTExprNode.h"
#include "ASTBlockNode.h"

namespace AST {

    ASTWhileNode::ASTWhileNode(const ASTExprNode *expr, const ASTBlockNode *block) : expr(expr), block(block) {}

    const ASTExprNode *ASTWhileNode::getExpr() const {
        return expr;
    }

    const ASTBlockNode *ASTWhileNode::getBlock() const {
        return block;
    }

    void ASTWhileNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTWhileNode::~ASTWhileNode(void) {
        delete expr;
        delete block;
    }
}