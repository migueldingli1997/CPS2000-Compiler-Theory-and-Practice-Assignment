#include <iostream>
#include <cmath>
#include "InterpreterExecVisitor.h"
#include "../../General/GeneralASTIncludes.h"
#include "../../General/Exceptions.h"

namespace VST {
    namespace InterpExec {

        using namespace std;
        using namespace AST;

        void InterpreterExecVisitor::setAnsValue(const string name, const Value newValue) {

            if (ST.lookup(name) == NOTFOUND) {
                ST.insert(name, newValue);
            } else {
                ST.modify(name, newValue);
            }
        }

        const SymbolTable *InterpreterExecVisitor::getST(void) const {
            return &ST;
        }

        const Value &InterpreterExecVisitor::getLastValue() const {
            return lastValue;
        }

        void InterpreterExecVisitor::visit(const ASTProgramNode *node) {

            // Initialization
            allowBlockScope = true;
            functionReturned = false;

            // Note: global scope is pushed and popped by symbol table itself
            try {
                for (auto &stmt : node->getStmts()) {
                    stmt->Accept(this);
                }
            } catch (InterpreterError err1) { // Pop all scopes except for global scope
                try {
                    while (true) {
                        ST.pop();
                    }
                } catch (FatalSymbolTableError err2) {
                    throw err1;
                }
            }
        }

        void InterpreterExecVisitor::visit(const ASTBinExprNode *node) {

            node->getExpr1()->Accept(this); // LHS
            Value subLastVal1 = lastValue;

            node->getExpr2()->Accept(this); // RHS
            Value subLastVal2 = lastValue;

            double numericResult; // in case of a numeric operation
            const string op = node->getOp();
            if (op == "and") {
                lastValue.setVal(subLastVal1.getBoolVal() && subLastVal2.getBoolVal());
                return;
            } else if (op == "or") {
                lastValue.setVal(subLastVal1.getBoolVal() || subLastVal2.getBoolVal());
                return;
            } else if (op == "+") {
                if (subLastVal1.getType() == String || subLastVal2.getType() == String) {
                    lastValue.setVal(subLastVal1.toString() + subLastVal2.toString());
                    return;
                } else {
                    numericResult = subLastVal1.getNumericVal() + subLastVal2.getNumericVal();
                }
            } else if (op == "-") {
                numericResult = subLastVal1.getNumericVal() - subLastVal2.getNumericVal();
            } else if (op == "*") {
                numericResult = subLastVal1.getNumericVal() * subLastVal2.getNumericVal();
            } else if (op == "/") {
                numericResult = subLastVal1.getNumericVal() / subLastVal2.getNumericVal();
            } else if (op == ">") {
                lastValue.setVal(subLastVal1.getNumericVal() > subLastVal2.getNumericVal());
                return;
            } else if (op == ">=") {
                lastValue.setVal(subLastVal1.getNumericVal() >= subLastVal2.getNumericVal());
                return;
            } else if (op == "<") {
                lastValue.setVal(subLastVal1.getNumericVal() < subLastVal2.getNumericVal());
                return;
            } else if (op == "<=") {
                lastValue.setVal(subLastVal1.getNumericVal() <= subLastVal2.getNumericVal());
                return;
            } else if (op == "==") {
                lastValue.setVal(subLastVal1.getNumericVal() == subLastVal2.getNumericVal());
                return;
            } else if (op == "!=") {
                lastValue.setVal(subLastVal1.getNumericVal() != subLastVal2.getNumericVal());
                return;
            } else {
                throw FatalInterpreterError("unrecognized binary operator.");
            }

            // Rounding if result supposed to be an integer
            if (subLastVal1.getType() == Int && subLastVal2.getType() == Int) {
                int intNumericResult = (int) (numericResult + (numericResult < 0 ? -0.5 : 0.5));
                lastValue.setVal(intNumericResult); // allows for up to 0.5 double inaccuracy
            } else {
                lastValue.setVal(numericResult); // return value as is
            }
        }

        void InterpreterExecVisitor::visit(const ASTSubExprNode *node) {

            node->getExpr()->Accept(this);
            // lastValue should have been set by expression in the subexpression
        }

        void InterpreterExecVisitor::visit(const ASTBoolNode *node) {
            lastValue.setVal(node->getValue());
        }

        void InterpreterExecVisitor::visit(const ASTIntNode *node) {
            lastValue.setVal(node->getValue());
        }

        void InterpreterExecVisitor::visit(const ASTRealNode *node) {
            lastValue.setVal(node->getValue());
        }

        void InterpreterExecVisitor::visit(const ASTStringNode *node) {
            lastValue.setVal(node->getValue());
        }

        void InterpreterExecVisitor::visit(const ASTUnaryNode *node) {

            node->getExpr()->Accept(this);

            switch (lastValue.getType()) {
                case Bool: // operator assumed to be 'not'
                    lastValue.setVal(!lastValue.getBoolVal());
                    break;
                case Int: // operator assumed to be minus
                    lastValue.setVal(-lastValue.getIntVal());
                    break;
                case Real: // operator assumed to be minus
                    lastValue.setVal(-lastValue.getRealVal());
                    break;
                default:
                    throw FatalInterpreterError("unexpected type of last value.");
            }
        }

        void InterpreterExecVisitor::visit(const ASTIdentifierNode *node) {

            // ASTIdentifierNode only expected to be directly visited as identifier of existing variable
            lastValue = ST.getValue(node->getStr()).value;
        }

        void InterpreterExecVisitor::visit(const ASTFuncCallNode *node) {

            SymbolTableValue value = ST.getValue(node->getIdentifier()->getStr());
            const std::vector<const ASTExprNode *> *ap = &node->getParams()->getParams();
            const std::vector<const ASTFormalParamNode *> *fp = &value.formalParams->getParams();

            ST.push();

            // Assign values to parameters
            for (unsigned int i = 0; i < fp->size(); i++) {
                ap->at(i)->Accept(this);
                ST.insert(fp->at(i)->getIdentifier()->getStr(), lastValue);
            }

            // Traverse function body
            for (auto &stmt : value.value.getFunctionVal()->getBlock()->getStmts()) {
                stmt->Accept(this);
                if (functionReturned) {
                    break;
                }
            }

            // Check that function actually returned a value
            if (!functionReturned) {
                throw InterpreterError("function " + value.value.getFunctionVal()->getIdentifier()->getStr() +
                                       " did not return any value.");
            }
            functionReturned = false;

            ST.pop();
            // lastValue should have been set by the return
        }

        // Refer to ASTFuncCallNode visit function
        void InterpreterExecVisitor::visit(const ASTActualParamsNode *node) {}

        void InterpreterExecVisitor::visit(const ASTVarDeclNode *node) {

            node->getExpr()->Accept(this);
            ST.insert(node->getIdentifier()->getStr(), lastValue);
        }

        void InterpreterExecVisitor::visit(const ASTAssignNode *node) {

            node->getExpr()->Accept(this);
            ST.modify(node->getIdentifier()->getStr(), lastValue);
        }

        void InterpreterExecVisitor::visit(const ASTPrintNode *node) {

            node->getExpr()->Accept(this);
            cout << lastValue.toString() << endl; // adds a newline
        }

        void InterpreterExecVisitor::visit(const ASTIfNode *node) {

            node->getExpr()->Accept(this);
            if (lastValue.getBoolVal()) {
                node->getIfBlock()->Accept(this);
            } else if (node->getElseBlock() != nullptr) {
                node->getElseBlock()->Accept(this);
            }
        }

        void InterpreterExecVisitor::visit(const ASTWhileNode *node) {

            while (true) {
                node->getExpr()->Accept(this);
                if (lastValue.getBoolVal()) {
                    node->getBlock()->Accept(this);
                } else {
                    break;
                }
            }
        }

        void InterpreterExecVisitor::visit(const ASTReturnNode *node) {

            node->getExpr()->Accept(this);
            functionReturned = true;
            // lastValue should have been set by expression in the return
        }

        void InterpreterExecVisitor::visit(const ASTFuncDeclNode *node) {

            Value blockVal = Value();
            blockVal.setVal(node);
            ST.insert(node->getIdentifier()->getStr(), blockVal, node->getParams());
        }

        // Refer to ASTFuncDeclNode visit function
        void InterpreterExecVisitor::visit(const ASTFormalParamsNode *node) {}

        // Refer to ASTFuncDeclNode visit function
        void InterpreterExecVisitor::visit(const ASTFormalParamNode *node) {}

        void InterpreterExecVisitor::visit(const ASTBlockNode *node) {

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
