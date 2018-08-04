#ifndef CPS2000_ASTBINEXPRNODE_H
#define CPS2000_ASTBINEXPRNODE_H

#include "../ASTExprNode.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTBinExprNode final : public ASTExprNode {

    public:
        ASTBinExprNode(const ASTExprNode *expr1, const ASTExprNode *expr2, const std::string &op);

        const ASTExprNode *getExpr1() const;

        const ASTExprNode *getExpr2() const;

        const std::string &getOp() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTBinExprNode(void);

    private:
        const ASTExprNode *expr1;
        const ASTExprNode *expr2;
        const std::string op;
    };
}

#endif //CPS2000_ASTBINEXPRNODE_H
