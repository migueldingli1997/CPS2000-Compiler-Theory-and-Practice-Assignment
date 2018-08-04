#include "PrintXmlVisitor.h"
#include <iostream>
#include <fstream>
#include "../../General/GeneralASTIncludes.h"
#include "../../General/Exceptions.h"

namespace VST {
    namespace PrintXml {

        using namespace std;
        using namespace AST;

        PrintXmlVisitor::PrintXmlVisitor(ostream &output) : output(output) {
            if (output.fail()) {
                throw FatalXmlVisitorError("invalid output steam. Cannot output XML.");
            }
        }

        const std::string PrintXmlVisitor::getIndentation(void) {

            std::string tabs = "";
            for (int i = 0; i < indentation; i++) {
                tabs.append("\t");
            }
            return tabs;
        }

        void PrintXmlVisitor::visit(const ASTProgramNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<Program>" << endl;

            indentation++;
            for (auto &stmt : node->getStmts()) {
                stmt->Accept(this);
            }
            indentation--;

            output << tabs << "</Program>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTBinExprNode *node) {

            const std::string tabs = getIndentation();
            std::string op = node->getOp();
            if (op[0] == '<') {
                // Replace '<' with "&lt;" and add equals if operator is <=
                op = "&lt;" + op.substr(1);
            } else if (op[0] == '>') {
                // Replace '>' with "&gt;" and add equals if operator is >=
                op = "&gt;" + op.substr(1);
            }
            output << tabs << "<Binary op=\"" << op << "\">" << endl;

            indentation++;
            node->getExpr1()->Accept(this);
            node->getExpr2()->Accept(this);
            indentation--;

            output << tabs << "</Binary>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTSubExprNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<SubExpression>" << endl;

            indentation++;
            node->getExpr()->Accept(this);
            indentation--;

            output << tabs << "</SubExpression>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTBoolNode *node) {

            const std::string tabs = getIndentation();
            const std::string boolStr = node->getValue() ? "true" : "false";
            output << tabs << "<Boolean>" << boolStr << "</Boolean>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTIntNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<Integer>" << node->getValue() << "</Integer>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTRealNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<Real>" << node->getValue() << "</Real>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTStringNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<String>" << node->getValue() << "</String>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTUnaryNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<Unary op=\"" << node->getOp() << "\">" << endl;

            indentation++;
            node->getExpr()->Accept(this);
            indentation--;

            output << tabs << "</Unary>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTIdentifierNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<Identifier>" << node->getStr() << "</Identifier>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTFuncCallNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<FunctionCall>" << endl;

            indentation++;
            node->getIdentifier()->Accept(this);
            node->getParams()->Accept(this);
            indentation--;

            output << tabs << "</FunctionCall>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTActualParamsNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<ActualParameters>" << endl;

            indentation++;
            for (auto &param : node->getParams()) {
                param->Accept(this);
            }
            indentation--;

            output << tabs << "</ActualParameters>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTVarDeclNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<VarDeclaration type=\"" << TypeNames[node->getType()] << "\">" << endl;

            indentation++;
            node->getIdentifier()->Accept(this);
            output << tabs << "\t" << "<Expression>" << endl;  // added for distinction
            indentation++;
            node->getExpr()->Accept(this);
            indentation--;
            output << tabs << "\t" << "</Expression>" << endl; // added for distinction
            indentation--;

            output << tabs << "</VarDeclaration>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTAssignNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<Assignment>" << endl;

            indentation++;
            node->getIdentifier()->Accept(this);
            output << tabs << "\t" << "<Expression>" << endl;  // added for distinction
            indentation++;
            node->getExpr()->Accept(this);
            indentation--;
            output << tabs << "\t" << "</Expression>" << endl; // added for distinction
            indentation--;

            output << tabs << "</Assignment>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTPrintNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<Print>" << endl;

            indentation++;
            node->getExpr()->Accept(this);
            indentation--;

            output << tabs << "</Print>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTIfNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<If>" << endl;

            indentation++;
            node->getExpr()->Accept(this);
            node->getIfBlock()->Accept(this);
            if (node->getElseBlock() != nullptr) {
                node->getElseBlock()->Accept(this);
            }
            indentation--;

            output << tabs << "</If>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTWhileNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<While>" << endl;

            indentation++;
            node->getExpr()->Accept(this);
            node->getBlock()->Accept(this);
            indentation--;

            output << tabs << "</While>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTReturnNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<Return>" << endl;

            indentation++;
            node->getExpr()->Accept(this);
            indentation--;

            output << tabs << "</Return>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTFuncDeclNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<FnDeclaration type=\"" << TypeNames[node->getType()] << "\">" << endl;

            indentation++;
            node->getIdentifier()->Accept(this);
            node->getParams()->Accept(this);
            node->getBlock()->Accept(this);
            indentation--;

            output << tabs << "</FnDeclaration>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTFormalParamsNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<FormalParameters>" << endl;

            indentation++;
            for (auto &param : node->getParams()) {
                param->Accept(this);
            }
            indentation--;

            output << tabs << "</FormalParameters>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTFormalParamNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<FormalParameter type=\"" << TypeNames[node->getType()] << "\">" << endl;

            indentation++;
            node->getIdentifier()->Accept(this);
            indentation--;

            output << tabs << "</FormalParameter>" << endl;
        }

        void PrintXmlVisitor::visit(const ASTBlockNode *node) {

            const std::string tabs = getIndentation();
            output << tabs << "<Block>" << endl;

            indentation++;
            for (auto &stmt : node->getStmts()) {
                stmt->Accept(this);
            }
            indentation--;

            output << tabs << "</Block>" << endl;
        }
    }
}