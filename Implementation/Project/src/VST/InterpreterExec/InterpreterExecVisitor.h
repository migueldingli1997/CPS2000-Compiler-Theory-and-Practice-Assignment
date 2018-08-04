#ifndef PROJECT_INTERPRETEREXECVISITOR_H
#define PROJECT_INTERPRETEREXECVISITOR_H

#include "../Visitor.h"
#include "Value.h"
#include "SymbolTable.h"

namespace VST {
    namespace InterpExec {

        class Value;

        class InterpreterExecVisitor final : public Visitor {

        private:
            SymbolTable ST = SymbolTable(); // symbol table (for identifiers)
            Value lastValue = Value(); // indicates value of last evaluated expression

            // These are initialized in visit for ASTProgramNode
            bool allowBlockScope; // set to false to disable next block's scope
            bool functionReturned; // indicates if a function called returned

        public:
            void setAnsValue(const string name, const Value newValue);

            const SymbolTable *getST(void) const;

            const Value &getLastValue() const;

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

#endif //PROJECT_INTERPRETEREXECVISITOR_H
