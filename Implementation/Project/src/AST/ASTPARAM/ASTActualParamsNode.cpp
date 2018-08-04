#include "ASTActualParamsNode.h"
#include "../ASTExprNode.h"

namespace AST {

    ASTActualParamsNode::ASTActualParamsNode(const std::vector<const ASTExprNode *> &params) : params(params) {}

    const std::vector<const ASTExprNode *> &ASTActualParamsNode::getParams() const {
        return params;
    }

    void ASTActualParamsNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTActualParamsNode::~ASTActualParamsNode(void) {
        for (auto &param : params) {
            delete param;
        }
    }
}