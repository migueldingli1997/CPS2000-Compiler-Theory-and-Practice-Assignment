#include <iostream>
#include "DFA.h"
#include "../General/Token.h"
#include "../General/Exceptions.h"

namespace LEX {
    
    using namespace std;

    const int DFA::TRANS_TABLE[NUMBER_OF_STATES][NUMBER_OF_CATEGORIES] = {  /*
         Dgit DecP Lett Prnt Star Fwsl PlMn GrLs Excl Eqls UndS Quot Pnct NewL EofF Othr  */
        {S01, ERR, S04, ERR, S13, S07, S14, S15, S17, S16, S04, S05, S19, ERR, S20, ERR}, /*S00*/
        {S01, S02, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}, /*S01*/
        {S03, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}, /*S02*/
        {S03, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}, /*S03*/
        {S04, ERR, S04, ERR, ERR, ERR, ERR, ERR, ERR, ERR, S04, ERR, ERR, ERR, ERR, ERR}, /*S04*/
        {S05, S05, S05, S05, S05, S05, S05, S05, S05, S05, S05, S06, S05, ERR, ERR, ERR}, /*S05*/
        {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}, /*S06*/
        {ERR, ERR, ERR, ERR, S10, S08, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}, /*S07*/
        {S08, S08, S08, S08, S08, S08, S08, S08, S08, S08, S08, S08, S08, S09, ERR, ERR}, /*S08*/
        {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}, /*S09*/
        {S10, S10, S10, S10, S11, S10, S10, S10, S10, S10, S10, S10, S10, S10, ERR, ERR}, /*S10*/
        {S10, S10, S10, S10, S11, S12, S10, S10, S10, S10, S10, S10, S10, S10, ERR, ERR}, /*S11*/
        {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}, /*S12*/
        {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}, /*S13*/
        {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}, /*S14*/
        {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, S18, ERR, ERR, ERR, ERR, ERR, ERR}, /*S15*/
        {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, S18, ERR, ERR, ERR, ERR, ERR, ERR}, /*S16*/
        {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, S18, ERR, ERR, ERR, ERR, ERR, ERR}, /*S17*/
        {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}, /*S18*/
        {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}, /*S19*/
        {ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR, ERR}  /*S20*/
    };

    Token DFA::finalStateToToken(const State state, const string lexeme) {

        if (isFinalState(state)) {

            switch (state) {
                case S01:
                    return Token(TK_Integer, lexeme, stoi(lexeme));
                case S03:
                    return Token(TK_Real, lexeme, stod(lexeme));
                case S06:
                    return Token(TK_String, lexeme.substr(1, lexeme.length() - 2)); // without inverted commas
                case S07:
                case S13:
                    return Token(TK_MulOp, lexeme);
                case S09:
                case S12:
                    return Token(TK_Comment, lexeme);
                case S14:
                    return Token(TK_AddOp, lexeme);
                case S15:
                case S18:
                    return Token(TK_RelOp, lexeme);
                case S16:
                    return Token(TK_Equals, lexeme);
                case S20:
                    return Token(TK_EOF, (char) EOF + "");
                default:
                    break;
            }

            if (state == S04) { // identifier

                if (lexeme == "set") {
                    return Token(TK_KW_Set, lexeme);
                } else if (lexeme == "var") {
                    return Token(TK_KW_Var, lexeme);
                } else if (lexeme == "def") {
                    return Token(TK_KW_Def, lexeme);
                } else if (lexeme == "print") {
                    return Token(TK_KW_Prnt, lexeme);
                } else if (lexeme == "return") {
                    return Token(TK_KW_Rtrn, lexeme);
                } else if (lexeme == "if") {
                    return Token(TK_KW_If, lexeme);
                } else if (lexeme == "else") {
                    return Token(TK_KW_Else, lexeme);
                } else if (lexeme == "while") {
                    return Token(TK_KW_While, lexeme);
                } else if (lexeme == "or" || lexeme == "not") {
                    return Token(TK_AddOp, lexeme);
                } else if (lexeme == "and") {
                    return Token(TK_MulOp, lexeme);
                } else if (lexeme == "real" || lexeme == "int" || lexeme == "bool" || lexeme == "string") {
                    return Token(TK_Type, lexeme);
                } else if (lexeme == "true" || lexeme == "false") {
                    return Token(TK_Bool, lexeme);
                } else {
                    return Token(TK_Identifier, lexeme);
                }
            } else if (state == S19) { // punctuation

                if (lexeme.length() == 1) {
                    switch (lexeme.at(0)) {
                        case ':':
                            return Token(TK_Colon, lexeme);
                        case '(':
                            return Token(TK_OpenBrck, lexeme);
                        case ')':
                            return Token(TK_ClosBrck, lexeme);
                        case ',':
                            return Token(TK_Comma, lexeme);
                        case ';':
                            return Token(TK_Semicolon, lexeme);
                        case '{':
                            return Token(TK_OpenCurly, lexeme);
                        case '}':
                            return Token(TK_ClosCurly, lexeme);
                        default:
                            throw FatalLexerError("unhandled punctuation.");
                    }
                } else {
                    throw FatalLexerError("punctuation longer than 1 character.");
                }
            } else {
                throw FatalLexerError("unhandled final state.");
            }
        } else {
            throw FatalLexerError("state was not a final state.");
        }
    }

    bool DFA::isFinalState(const int state) {

        switch (state) {
            case S01:
            case S03:
            case S04:
            case S06:
            case S07:
            case S09:
            case S12:
            case S13:
            case S14:
            case S15:
            case S16:
            case S18:
            case S19:
            case S20:
                return true;
            default:
                return false;
        }
    }
}