#ifndef CPS2000_LEXER_H
#define CPS2000_LEXER_H

#include <stack>
#include "DFA.h"

class Token;

namespace LEX {

    class Lexer {

    public:
        Lexer(std::istream &);

        Token getNextToken(void);

        int getCurrentLine() const;

    private:
        std::istream &source;

        std::stack<int> stateStack;
        int currLine;
        int currState;
        std::string lexeme;

        char getNextChar(void);
    };
}

#endif //CPS2000_LEXER_H
