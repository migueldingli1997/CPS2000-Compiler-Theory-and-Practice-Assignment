#ifndef CPS2000_ASTPROGRAMNODE_H
#define CPS2000_ASTPROGRAMNODE_H

#include <vector>
#include "ASTNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTStmtNode;

    class ASTProgramNode final : public ASTNode {

    public:
        ASTProgramNode(const std::vector<const ASTStmtNode *> &stmts);

        const std::vector<const ASTStmtNode *> &getStmts() const;

        virtual void Accept(VST::Visitor *v) const override;

        virtual ~ASTProgramNode(void);

    private:
        const std::vector<const ASTStmtNode *> stmts;
    };
}

#endif //CPS2000_ASTPROGRAMNODE_H
