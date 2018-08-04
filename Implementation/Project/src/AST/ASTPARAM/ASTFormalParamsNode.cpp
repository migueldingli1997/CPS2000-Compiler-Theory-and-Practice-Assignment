#include "ASTFormalParamsNode.h"
#include "ASTFormalParamNode.h"

namespace AST {
    ASTFormalParamsNode::ASTFormalParamsNode(const std::vector<const ASTFormalParamNode *> &params) :
            params(params) {}

    const std::vector<const ASTFormalParamNode *> &ASTFormalParamsNode::getParams() const {
        return params;
    }

    void ASTFormalParamsNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTFormalParamsNode::~ASTFormalParamsNode(void) {
        for (auto &param : params) {
            delete param;
        }
    }
}