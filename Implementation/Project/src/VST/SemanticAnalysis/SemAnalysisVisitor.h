#ifndef CPS2000_SEMANTICANALYSISVISITOR_H
#define CPS2000_SEMANTICANALYSISVISITOR_H

#include "../Visitor.h"
#include "SymbolTable.h"
#include "../../General/Type.h"

namespace VST {
    namespace SemAnalysis {

        class SemAnalysisVisitor final : public Visitor {

        private:
            SymbolTable ST = SymbolTable(); // symbol table (for identifiers)
            std::vector<Type> FL = std::vector<Type>(); // function list (for return types)

            Type lastType; // indicates the type of the last visited expression
            bool allowBlockScope; // set to false to disable next block's scope

            void checkThatExists(const AST::ASTIdentifierNode *identifier);

            void checkThatDoesNotExist(const AST::ASTIdentifierNode *identifier);

        public:
            void setAnsType(const std::string name, const Type newType);

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

#endif //CPS2000_SEMANTICANALYSISVISITOR_H
