#ifndef CPS2000_PRINTXMLVISITOR_H
#define CPS2000_PRINTXMLVISITOR_H

#include "../Visitor.h"
#include <string>

namespace VST {
    namespace PrintXml {

        class PrintXmlVisitor final : public Visitor {

        private:
            int indentation = 0;
            std::ostream &output;

            const std::string getIndentation(void);

        public:
            PrintXmlVisitor(std::ostream &);

            void visit(const AST::ASTProgramNode *node) override;

            void visit(const AST::ASTBinExprNode *node) override;

            void visit(const AST::ASTSubExprNode *node) override;

            void visit(const AST::ASTBoolNode *node) override;

            void visit(const AST::ASTIntNode *node) override;

            void visit(const AST::ASTRealNode *node) override;

            void visit(const AST::ASTStringNode *node) override;

            void visit(const AST::ASTUnaryNode *node) override;

            void visit(const AST::ASTIdentifierNode *node) override;

            void visit(const AST::ASTFuncCallNode *node) override;

            void visit(const AST::ASTActualParamsNode *node) override;

            void visit(const AST::ASTVarDeclNode *node) override;

            void visit(const AST::ASTAssignNode *node) override;

            void visit(const AST::ASTPrintNode *node) override;

            void visit(const AST::ASTIfNode *node) override;

            void visit(const AST::ASTWhileNode *node) override;

            void visit(const AST::ASTReturnNode *node) override;

            void visit(const AST::ASTFuncDeclNode *node) override;

            void visit(const AST::ASTFormalParamsNode *node) override;

            void visit(const AST::ASTFormalParamNode *node) override;

            void visit(const AST::ASTBlockNode *node) override;
        };
    }
}

#endif //CPS2000_PRINTXMLVISITOR_H
