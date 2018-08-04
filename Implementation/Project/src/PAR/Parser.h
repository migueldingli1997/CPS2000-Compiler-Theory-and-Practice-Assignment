#ifndef CPS2000_PARSER_H
#define CPS2000_PARSER_H

#include "../LEX/Lexer.h"
#include "../General/Token.h"
#include "../General/GeneralASTIncludes.h"

class Token;

namespace PAR {

    class Parser {

    public:
        Parser(LEX::Lexer &lexer);

        AST::ASTProgramNode *parse(void);

    private:
        LEX::Lexer &lexer;
        Token lookahead;

        Token match(const TkType tokenType);

        AST::ASTExprNode *parseFactor(void);

        AST::ASTExprNode *parseTerm(void);

        AST::ASTExprNode *parseSimpleExpression(void);

        AST::ASTExprNode *parseExpression(void);

        AST::ASTUnaryNode *parseUnary(void);

        AST::ASTExprNode *parseFuncCallOrIdentifier(void);

        AST::ASTActualParamsNode *parseActualParams(void);

        AST::ASTSubExprNode *parseSubExpression(void);

        AST::ASTStmtNode *parseStatement(void);

        AST::ASTVarDeclNode *parseVariableDeclaration(void);

        AST::ASTAssignNode *parseAssignment(void);

        AST::ASTPrintNode *parsePrintStatement(void);

        AST::ASTIfNode *parseIfStatement(void);

        AST::ASTWhileNode *parseWhileStatement(void);

        AST::ASTReturnNode *parseReturnStatement(void);

        AST::ASTFuncDeclNode *parseFuncDeclaration(void);

        AST::ASTFormalParamsNode *parseFormalParams(void);

        AST::ASTFormalParamNode *parseFormalParam(void);

        AST::ASTBlockNode *parseBlock(void);
    };
}

#endif //CPS2000_PARSER_H
