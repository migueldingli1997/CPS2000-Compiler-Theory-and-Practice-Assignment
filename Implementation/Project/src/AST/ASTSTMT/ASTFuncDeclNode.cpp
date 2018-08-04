#include "ASTFuncDeclNode.h"
#include "../ASTPARAM/ASTFormalParamsNode.h"
#include "../ASTEXPR/ASTIdentifierNode.h"
#include "ASTBlockNode.h"

namespace AST {

    ASTFuncDeclNode::ASTFuncDeclNode(const std::string &identifier, const ASTFormalParamsNode *params,
                                     const Type &type, const ASTBlockNode *block) :
            identifier(new ASTIdentifierNode(identifier)),
            params(params), type(type), block(block) {}

    const ASTIdentifierNode *ASTFuncDeclNode::getIdentifier(void) const {
        return identifier;
    }

    const ASTFormalParamsNode *ASTFuncDeclNode::getParams(void) const {
        return params;
    }

    const Type &ASTFuncDeclNode::getType(void) const {
        return type;
    }

    const ASTBlockNode *ASTFuncDeclNode::getBlock() const {
        return block;
    }

    void ASTFuncDeclNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTFuncDeclNode::~ASTFuncDeclNode(void) {
        delete identifier;
        delete params;
        delete block;
    }
}