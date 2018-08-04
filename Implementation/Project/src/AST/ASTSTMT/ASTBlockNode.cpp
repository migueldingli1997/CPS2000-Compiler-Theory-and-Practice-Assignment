#include "ASTBlockNode.h"

namespace AST {

    ASTBlockNode::ASTBlockNode(const std::vector<const ASTStmtNode *> &stmts) : stmts(stmts) {}

    const std::vector<const ASTStmtNode *> &ASTBlockNode::getStmts() const {
        return stmts;
    }

    void ASTBlockNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTBlockNode::~ASTBlockNode(void) {
        for (auto &stmt : stmts) {
            delete stmt;
        }
    }
}