#include "ASTFormalParamNode.h"
#include "../ASTEXPR/ASTIdentifierNode.h"

namespace AST {

    ASTFormalParamNode::ASTFormalParamNode(const std::string &identifier, const Type &type) :
            identifier(new ASTIdentifierNode(identifier)), type(type) {}

    const ASTIdentifierNode *ASTFormalParamNode::getIdentifier() const {
        return identifier;
    }

    const Type &ASTFormalParamNode::getType(void) const {
        return type;
    }

    void ASTFormalParamNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTFormalParamNode::~ASTFormalParamNode(void) {
        delete identifier;
    }
}