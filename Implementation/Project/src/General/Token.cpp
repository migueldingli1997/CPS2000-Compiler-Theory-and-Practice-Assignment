#include <iostream>
#include "Token.h"

Token::Token(const TkType type, const std::string name) : Token(type, name, 0) {}

Token::Token(const TkType type, const std::string name, const double value) : type(type), lexeme(name), value(value) {}

const TkType Token::getType() const {
    return type;
}

const std::string Token::getLexeme() const {
    return lexeme;
}

const double Token::getRealValue() const {
    return value;
}

const int Token::getIntValue() const {
    return (int) (value + (value < 0 ? -0.5 : +0.5));
}