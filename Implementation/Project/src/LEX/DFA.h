#ifndef CPS2000_DFA_H
#define CPS2000_DFA_H

#include <string>
#include "Category.h"
#include "State.h"

class Token;

namespace LEX {

    class DFA {

    public:
        const static int ERR = -2, BAD = -1, START = S00;
        const static int TRANS_TABLE[NUMBER_OF_STATES][NUMBER_OF_CATEGORIES];

        static Token finalStateToToken(const State state, const std::string lexeme);

        static bool isFinalState(const int state);
    };
}

#endif //CPS2000_DFA_H
