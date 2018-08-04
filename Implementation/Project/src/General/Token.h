#ifndef CPS2000_TOKEN_H
#define CPS2000_TOKEN_H

#include <ostream>

enum TkType {
    TK_Bool,
    TK_Integer,
    TK_Real,
    TK_String,
    TK_Identifier,
    TK_MulOp,
    TK_AddOp,
    TK_RelOp,
    TK_Equals,
    TK_Colon,
    TK_OpenBrck,
    TK_ClosBrck,
    TK_Comma,
    TK_Semicolon,
    TK_OpenCurly,
    TK_ClosCurly,
    TK_KW_Set,
    TK_KW_Var,
    TK_KW_Def,
    TK_KW_Prnt,
    TK_KW_Rtrn,
    TK_KW_If,
    TK_KW_Else,
    TK_KW_While,
    TK_Type,
    TK_Comment,
    TK_EOF,
    NUMBER_OF_TOKEN_TYPES
};

class Token {

public:
    Token(const TkType, const std::string);

    Token(const TkType, const std::string, const double);

    const TkType getType() const;

    const std::string getLexeme() const;

    const double getRealValue() const;

    const int getIntValue() const;

private:
    TkType type;
    std::string lexeme;
    double value;
};

#endif //CPS2000_TOKEN_H
