#include "ASTProgramNode.h"
#include "ASTStmtNode.h"

namespace AST {

    ASTProgramNode::ASTProgramNode(const std::vector<const ASTStmtNode *> &stmts) : stmts(stmts) {}

    const std::vector<const ASTStmtNode *> &ASTProgramNode::getStmts() const {
        return stmts;
    }

    void ASTProgramNode::Accept(VST::Visitor *v) const {
        v->visit(this);
    }

    ASTProgramNode::~ASTProgramNode(void) {
        for (auto &stmt : stmts) {
            delete stmt;
        }
    }
}