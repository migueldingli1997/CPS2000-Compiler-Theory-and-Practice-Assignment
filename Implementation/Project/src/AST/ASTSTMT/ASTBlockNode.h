#ifndef CPS2000_ASTBLOCKNODE_H
#define CPS2000_ASTBLOCKNODE_H

#include <vector>
#include "../ASTStmtNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTBlockNode final : public ASTStmtNode {

    public:
        ASTBlockNode(const std::vector<const ASTStmtNode *> &stmts);

        const std::vector<const ASTStmtNode *> &getStmts() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTBlockNode(void);

    private:
        const std::vector<const ASTStmtNode *> stmts;
    };
}

#endif //CPS2000_ASTBLOCKNODE_H
