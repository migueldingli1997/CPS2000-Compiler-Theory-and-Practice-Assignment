#include "ASTFuncCallNode.h"
#include "../ASTPARAM/ASTActualParamsNode.h"
#include "ASTIdentifierNode.h"

namespace AST {

    ASTFuncCallNode::ASTFuncCallNode(const std::string identifier, const ASTActualParamsNode *params) :
            identifier(new AST::ASTIdentifierNode(identifier)), params(params) {}

    const ASTIdentifierNode *ASTFuncCallNode::getIdentifier() const {
        return identifier;
    }

    const ASTActualParamsNode *ASTFuncCallNode::getParams() const {
        return params;
    }

    void ASTFuncCallNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTFuncCallNode::~ASTFuncCallNode(void) {
        delete identifier;
        delete params;
    }
}