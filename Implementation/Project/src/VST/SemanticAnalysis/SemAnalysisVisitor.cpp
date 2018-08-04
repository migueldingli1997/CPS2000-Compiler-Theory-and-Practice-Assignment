#include <iostream>
#include "SemAnalysisVisitor.h"
#include "../../General/GeneralASTIncludes.h"
#include "../../General/Exceptions.h"

namespace VST {
    namespace SemAnalysis {

        using namespace AST;
        using namespace std;

        void SemAnalysisVisitor::checkThatExists(const ASTIdentifierNode *identifier) {

            // Checks that identifier exists in all scopes (current and outer up to global)
            if (ST.lookup(identifier->getStr()) == NOTFOUND) {
                throw SemAnalysisError(string("identifier \"" + identifier->getStr() + "\" does not exist."));
            }
        }

        void SemAnalysisVisitor::checkThatDoesNotExist(const ASTIdentifierNode *identifier) {

            // Checks that identifier does not exist in current scope
            if (ST.lookup(identifier->getStr()) == INNERMOST) {
                throw SemAnalysisError(string("duplicate declaration of \"" + identifier->getStr() + "\"."));
            }
        }

        void SemAnalysisVisitor::setAnsType(const string name, const Type newType) {

            if (ST.lookup(name) == NOTFOUND) {
                ST.insert(name, newType);
            } else {
                ST.modify(name, newType);
            }
        }

        void SemAnalysisVisitor::visit(const ASTProgramNode *node) {

            // Initialization
            allowBlockScope = true;

            // Note: global scope is pushed and popped by symbol table itself
            try {
                for (auto &stmt : node->getStmts()) {
                    stmt->Accept(this);
                }
            } catch (SemAnalysisError err1) { // Pop all scopes except for global scope
                FL.clear();
                try {
                    while (true) {
                        ST.pop();
                    }
                } catch (FatalSymbolTableError err2) {
                    throw err1;
                }
            }
        }

        void SemAnalysisVisitor::visit(const ASTBinExprNode *node) {

            node->getExpr1()->Accept(this); // LHS
            const Type expr1Type = lastType;

            node->getExpr2()->Accept(this); // RHS
            const Type expr2Type = lastType;

            const string op = node->getOp();
            if (op == "and" || op == "or") {
                // 'and' and 'or' operators can only be applied to booleans
                if (expr1Type != Bool || expr2Type != Bool) {
                    const Type illegalType = expr1Type != Bool ? expr1Type : expr2Type;
                    throw SemAnalysisError_TypeMismatch(Bool, illegalType, ("\"" + op + "\" operation"));
                }
                lastType = Bool;
            } else if (op == "+" && (expr1Type == String || expr2Type == String)) {
                // Addition of string with any other type is allowed
                lastType = String;
            } else if (op == "+" || op == "-" || op == "*" || op == "/") {
                // Additive/multiplicative (excluding addition) cannot be applied on booleans or string
                if (expr1Type == Bool || expr1Type == String ||
                    expr2Type == Bool || expr2Type == String) {
                    throw SemAnalysisError_TypeMismatch("numeric type", "Bool or String", ("\"" + op + "\" operation"));
                }
                if (expr1Type == Real || expr2Type == Real) {
                    lastType = Real; // Real OP ___ = Real
                } else {
                    lastType = Int; // Int OP Int = Int
                }
            } else if (op[0] == '>' || op[0] == '<' || op == "==" || op == "!=") {
                // Relational operators cannot be applied on booleans or string
                if (expr1Type == Bool || expr1Type == String ||
                    expr2Type == Bool || expr2Type == String) {
                    throw SemAnalysisError_TypeMismatch("numeric type", "Bool or String", ("\"" + op + "\" operation"));
                }
                lastType = Bool;
            } else {
                throw FatalSemAnalysisError("unrecognized binary operator.");
            }
        }

        void SemAnalysisVisitor::visit(const ASTSubExprNode *node) {

            node->getExpr()->Accept(this);
            // lastType should have been set by expression in the subexpression
        }

        void SemAnalysisVisitor::visit(const ASTBoolNode *node) { lastType = Bool; }

        void SemAnalysisVisitor::visit(const ASTIntNode *node) { lastType = Int; }

        void SemAnalysisVisitor::visit(const ASTRealNode *node) { lastType = Real; }

        void SemAnalysisVisitor::visit(const ASTStringNode *node) { lastType = String; }

        void SemAnalysisVisitor::visit(const ASTUnaryNode *node) {

            node->getExpr()->Accept(this);

            const string op = node->getOp();
            if (op == "not" && lastType != Bool) {
                // 'not' can only be applied to booleans
                throw SemAnalysisError_TypeMismatch(Bool, lastType, "unary \"not\" operation");
            } else if (op == "-" && (lastType == Bool || lastType == String)) {
                // Minus not applicable to boolean or string
                throw SemAnalysisError_TypeMismatch("numeric type", TypeNames[lastType], "unary \"-\" operation");
            } else if (op != "not" && op != "-") {
                throw FatalSemAnalysisError("unrecognized unary operator.");
            }
            // lastType should have been set by expression in the unary
        }

        void SemAnalysisVisitor::visit(const ASTIdentifierNode *node) {

            // ASTIdentifierNode only expected to be directly visited as identifier of existing variable
            checkThatExists(node);

            // Identifier shouldn't have associated parameters since it identifies an existing variable
            SymbolTableValue stValue = ST.getValue(node->getStr());
            if (stValue.formalParams != nullptr) {
                throw SemAnalysisError("function " + node->getStr() + " is used as a variable.");
            }
            lastType = stValue.type;
        }

        void SemAnalysisVisitor::visit(const ASTFuncCallNode *node) {

            checkThatExists(node->getIdentifier()); // function has to exist
            SymbolTableValue value = ST.getValue(node->getIdentifier()->getStr());
            const ASTFormalParamsNode *formalParams = value.formalParams;

            if (formalParams == nullptr) {
                throw SemAnalysisError("identifier " + node->getIdentifier()->getStr() + " is not a function.");
            } else if (node->getParams()->getParams().size() != formalParams->getParams().size()) {
                throw SemAnalysisError(node->getIdentifier()->getStr() + " given incorrect number of arguments.");
            }

            unsigned long arg = 0;
            for (auto &param : node->getParams()->getParams()) {
                param->Accept(this);
                const ASTFormalParamNode *formalParam = formalParams->getParams().at(arg++);
                if (lastType != formalParam->getType()) {
                    throw SemAnalysisError_TypeMismatch(formalParam->getType(), lastType,
                                                        "argument " + formalParam->getIdentifier()->getStr() +
                                                        " to function " + node->getIdentifier()->getStr());
                }
            }
            lastType = value.type;
        }

        // Refer to ASTFuncCallNode visit function
        void SemAnalysisVisitor::visit(const ASTActualParamsNode *node) {}

        void SemAnalysisVisitor::visit(const ASTVarDeclNode *node) {

            checkThatDoesNotExist(node->getIdentifier()); // variable identifier cannot exist

            node->getExpr()->Accept(this);
            const Type expectedType = node->getType();
            if (lastType != expectedType) {
                throw SemAnalysisError_TypeMismatch(expectedType, lastType,
                                                    "declaration of variable " + node->getIdentifier()->getStr());
            }

            // Identifier inserted after so that it is not used by above expression
            ST.insert(node->getIdentifier()->getStr(), node->getType());
        }

        void SemAnalysisVisitor::visit(const ASTAssignNode *node) {

            checkThatExists(node->getIdentifier()); // variable has to exist
            node->getExpr()->Accept(this);

            const Type expectedType = ST.getValue(node->getIdentifier()->getStr()).type;
            if (lastType != expectedType) {
                throw SemAnalysisError_TypeMismatch(expectedType, lastType,
                                                    "assignment of variable " + node->getIdentifier()->getStr());
            }
        }

        void SemAnalysisVisitor::visit(const ASTPrintNode *node) {
            node->getExpr()->Accept(this);
        }

        void SemAnalysisVisitor::visit(const ASTIfNode *node) {

            node->getExpr()->Accept(this);
            if (lastType != Bool) {
                throw SemAnalysisError_TypeMismatch(Bool, lastType, "if statement condition");
            }
            node->getIfBlock()->Accept(this);
            if (node->getElseBlock() != nullptr) {
                node->getElseBlock()->Accept(this);
            }
        }

        void SemAnalysisVisitor::visit(const ASTWhileNode *node) {

            node->getExpr()->Accept(this);
            if (lastType != Bool) {
                throw SemAnalysisError_TypeMismatch(Bool, lastType, "while loop condition");
            }
            node->getBlock()->Accept(this);
        }

        void SemAnalysisVisitor::visit(const ASTReturnNode *node) {

            node->getExpr()->Accept(this);
            if (FL.size() == 0) {
                throw SemAnalysisError("attempted to return outside of a function body.");
            } else if (lastType != FL.back()) {
                throw SemAnalysisError_TypeMismatch(FL.back(), lastType, "function return statement");
            }
        }

        void SemAnalysisVisitor::visit(const ASTFuncDeclNode *node) {

            checkThatDoesNotExist(node->getIdentifier()); // function identifier cannot exist
            ST.insert(node->getIdentifier()->getStr(), node->getType(), node->getParams());

            //New scope starts from after function name
            ST.push();
            FL.push_back(node->getType());
            for (auto &param : node->getParams()->getParams()) {
                ST.insert(param->getIdentifier()->getStr(), param->getType());
            }

            // Below, the new scope is disabled for block so that the function
            // parameters are in same scope as the statements in the block.
            allowBlockScope = false;
            node->getBlock()->Accept(this);

            ST.pop();
            FL.pop_back();
        }

        // Refer to ASTFuncDeclNode visit function
        void SemAnalysisVisitor::visit(const ASTFormalParamsNode *node) {}

        // Refer to ASTFuncDeclNode visit function
        void SemAnalysisVisitor::visit(const ASTFormalParamNode *node) {}

        void SemAnalysisVisitor::visit(const ASTBlockNode *node) {

            // Scope can be disabled (for function declaration)
            const bool createNewScope = allowBlockScope; // to be used just for below
            allowBlockScope = true; // boolean reset

            if (createNewScope) {
                ST.push();
            }
            for (auto &stmt : node->getStmts()) {
                stmt->Accept(this);
            }
            if (createNewScope) {
                ST.pop();
            }
        }
    }
}