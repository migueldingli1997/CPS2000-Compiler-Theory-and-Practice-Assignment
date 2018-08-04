#include <iostream>
#include "Parser.h"
#include "../General/Exceptions.h"

namespace PAR {

    using namespace AST;
    using namespace std;

    Parser::Parser(LEX::Lexer &lexer) : lexer(lexer), lookahead(lexer.getNextToken()) {}

    ASTProgramNode *Parser::parse(void) {

        vector<const ASTStmtNode *> stmts = vector<const ASTStmtNode *>();

        // Parse statements until token is an end-of-file token
        while (lookahead.getType() != TK_EOF) {
            stmts.push_back(parseStatement());
        }
        return new ASTProgramNode(stmts);
    }

    Token Parser::match(const TkType tokenType) {

        // Confirm that current token is of expected type
        if (lookahead.getType() == tokenType) {
            // Get next token and return previous
            const Token previousToken = lookahead;
            lookahead = lexer.getNextToken();
            return previousToken;
        } else {
            throw ParserError_SyntaxError(lexer.getCurrentLine(), "unexpected token \"" + lookahead.getLexeme() + "\"");
        }
    }

    ASTExprNode *Parser::parseFactor(void) {

        switch (lookahead.getType()) {

            case TK_Bool: { // Literal (Type 1)
                Token boolTok = match(TK_Bool);
                if (boolTok.getLexeme() == "true") {
                    return new ASTBoolNode(true);
                } else if (boolTok.getLexeme() == "false") {
                    return new ASTBoolNode(false);
                } else {
                    throw FatalParserError("invalid TK_Bool value.");
                }
            }
            case TK_Integer: // Literal (Type 2)
                return new ASTIntNode(match(TK_Integer).getIntValue());
            case TK_Real: // Literal (Type 3)
                return new ASTRealNode(match(TK_Real).getRealValue());
            case TK_String: // Literal (Type 4)
                return new ASTStringNode(match(TK_String).getLexeme());
            case TK_Identifier: // Function call and identifier
                return parseFuncCallOrIdentifier();
            case TK_OpenBrck: // Sub-expression
                return parseSubExpression();
            case TK_AddOp: // Assumed to be a unary (assumption verified in parseUnary())
                return parseUnary();
            default:
                throw ParserError_SyntaxError(lexer.getCurrentLine(), "invalid or missing factor");
        }
    }

    ASTExprNode *Parser::parseTerm(void) {

        ASTExprNode *factor = parseFactor();

        if (lookahead.getType() == TK_MulOp) {
            Token op = match(TK_MulOp);
            ASTExprNode *term = parseTerm();
            return new ASTBinExprNode(factor, term, op.getLexeme());
        } else {
            return factor;
        }
    }

    ASTExprNode *Parser::parseSimpleExpression(void) {

        ASTExprNode *term = parseTerm();

        if (lookahead.getType() == TK_AddOp) {
            Token op = match(TK_AddOp);
            ASTExprNode *simpExpr = parseSimpleExpression();
            return new ASTBinExprNode(term, simpExpr, op.getLexeme());
        } else {
            return term;
        }
    }

    ASTExprNode *Parser::parseExpression(void) {

        ASTExprNode *simpExpr = parseSimpleExpression();

        if (lookahead.getType() == TK_RelOp) {
            Token op = match(TK_RelOp);
            ASTExprNode *expr = parseExpression();
            return new ASTBinExprNode(simpExpr, expr, op.getLexeme());
        } else {
            return simpExpr;
        }
    }

    ASTUnaryNode *Parser::parseUnary(void) {

        const string lexeme = lookahead.getLexeme();
        if (lexeme == "-" || lexeme == "not") {
            Token op = match(TK_AddOp);
            ASTExprNode *expr = parseExpression();
            return new ASTUnaryNode(op.getLexeme(), expr);
        } else {
            throw ParserError_SyntaxError(lexer.getCurrentLine(), "invalid unary operator");
        }
    }

    ASTExprNode *Parser::parseFuncCallOrIdentifier(void) {

        Token identifier = match(TK_Identifier);
        if (lookahead.getType() == TK_OpenBrck) {
            match(TK_OpenBrck);
            ASTActualParamsNode *params = parseActualParams();
            match(TK_ClosBrck);
            return new ASTFuncCallNode(identifier.getLexeme(), params);
        } else {
            return new ASTIdentifierNode(identifier.getLexeme());
        }
    }

    ASTActualParamsNode *Parser::parseActualParams(void) {

        vector<const ASTExprNode *> params = vector<const ASTExprNode *>();
        if (lookahead.getType() != TK_ClosBrck) {
            params.push_back(parseExpression());
            while (lookahead.getType() == TK_Comma) {
                match(TK_Comma);
                params.push_back(parseExpression());
            }
        }
        return new ASTActualParamsNode(params);
    }

    ASTSubExprNode *Parser::parseSubExpression(void) {

        match(TK_OpenBrck);
        ASTExprNode *expr = parseExpression();
        match(TK_ClosBrck);
        return new ASTSubExprNode(expr);
    }

    ASTStmtNode *Parser::parseStatement(void) {

        switch (lookahead.getType()) {

            case TK_KW_Var: // variable declaration
                return parseVariableDeclaration();
            case TK_KW_Set: // assignment
                return parseAssignment();
            case TK_KW_Prnt: // print statement
                return parsePrintStatement();
            case TK_KW_If: // if statement
                return parseIfStatement();
            case TK_KW_While: // while statement
                return parseWhileStatement();
            case TK_KW_Rtrn: // return statement
                return parseReturnStatement();
            case TK_KW_Def: // function declaration
                return parseFuncDeclaration();
            case TK_OpenCurly: // block
                return parseBlock();
            default:
                throw ParserError_SyntaxError(lexer.getCurrentLine(), "invalid start of statement");
        }
    }

    ASTVarDeclNode *Parser::parseVariableDeclaration(void) {

        match(TK_KW_Var);
        Token id = match(TK_Identifier);
        match(TK_Colon);
        Token type = match(TK_Type);
        match(TK_Equals);
        ASTExprNode *expr = parseExpression();
        match(TK_Semicolon);
        return new ASTVarDeclNode(id.getLexeme(), strToType(type.getLexeme()), expr);
    }

    ASTAssignNode *Parser::parseAssignment(void) {

        match(TK_KW_Set);
        Token id = match(TK_Identifier);
        match(TK_Equals);
        ASTExprNode *expr = parseExpression();
        match(TK_Semicolon);
        return new ASTAssignNode(id.getLexeme(), expr);
    }

    ASTPrintNode *Parser::parsePrintStatement(void) {

        match(TK_KW_Prnt);
        ASTExprNode *expr = parseExpression();
        match(TK_Semicolon);
        return new ASTPrintNode(expr);
    }

    ASTIfNode *Parser::parseIfStatement(void) {

        match(TK_KW_If);
        match(TK_OpenBrck);
        ASTExprNode *expr = parseExpression();
        match(TK_ClosBrck);
        ASTBlockNode *ifBlock = parseBlock();
        ASTBlockNode *elseBlock;
        if (lookahead.getType() == TK_KW_Else) {
            match(TK_KW_Else);
            elseBlock = parseBlock();
        } else {
            elseBlock = nullptr;
        }
        return new ASTIfNode(expr, ifBlock, elseBlock);
    }

    ASTWhileNode *Parser::parseWhileStatement(void) {

        match(TK_KW_While);
        match(TK_OpenBrck);
        ASTExprNode *expr = parseExpression();
        match(TK_ClosBrck);
        ASTBlockNode *block = parseBlock();
        return new ASTWhileNode(expr, block);
    }

    ASTReturnNode *Parser::parseReturnStatement(void) {

        match(TK_KW_Rtrn);
        ASTExprNode *expr = parseExpression();
        match(TK_Semicolon);
        return new ASTReturnNode(expr);
    }

    ASTFuncDeclNode *Parser::parseFuncDeclaration(void) {

        match(TK_KW_Def);
        Token id = match(TK_Identifier);
        match(TK_OpenBrck);
        ASTFormalParamsNode *params = parseFormalParams(); // optional
        match(TK_ClosBrck);
        match(TK_Colon);
        Token type = match(TK_Type);
        ASTBlockNode *block = parseBlock();
        return new ASTFuncDeclNode(id.getLexeme(), params, strToType(type.getLexeme()), block);
    }

    ASTFormalParamsNode *Parser::parseFormalParams(void) {

        vector<const ASTFormalParamNode *> params = vector<const ASTFormalParamNode *>();
        if (lookahead.getType() != TK_ClosBrck) {
            params.push_back(parseFormalParam());
            while (lookahead.getType() == TK_Comma) {
                match(TK_Comma);
                params.push_back(parseFormalParam());
            }
        }
        return new ASTFormalParamsNode(params);
    }

    ASTFormalParamNode *Parser::parseFormalParam(void) {

        Token id = match(TK_Identifier);
        match(TK_Colon);
        Token type = match(TK_Type);
        return new ASTFormalParamNode(id.getLexeme(), strToType(type.getLexeme()));
    }

    ASTBlockNode *Parser::parseBlock(void) {

        vector<const ASTStmtNode *> stmts = vector<const ASTStmtNode *>();

        match(TK_OpenCurly);
        while (lookahead.getType() != TK_ClosCurly) {
            stmts.push_back(parseStatement());
        }
        match(TK_ClosCurly);
        return new ASTBlockNode(stmts);
    }
}