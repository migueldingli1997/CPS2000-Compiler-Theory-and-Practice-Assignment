#ifndef CPS2000_ASTFUNCDECLNODE_H
#define CPS2000_ASTFUNCDECLNODE_H

#include "../ASTStmtNode.h"
#include "../../General/Type.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTFormalParamsNode;

    class ASTBlockNode;

    class ASTFuncDeclNode final : public ASTStmtNode {

    public:
        ASTFuncDeclNode(const std::string &identifier, const ASTFormalParamsNode *params, const Type &type,
                        const ASTBlockNode *block);

        const ASTIdentifierNode *getIdentifier() const;

        const ASTFormalParamsNode *getParams() const;

        const Type &getType() const;

        const ASTBlockNode *getBlock() const;

        void Accept(VST::Visitor *v) const override;

        virtual ~ASTFuncDeclNode(void);

    private:
        const ASTIdentifierNode *identifier;
        const ASTFormalParamsNode *params;
        const Type type;
        const ASTBlockNode *block;
    };
}

#endif //CPS2000_ASTFUNCDECLNODE_H
