#include <iostream>
#include "Lexer.h"
#include "../General/Token.h"
#include "../General/Exceptions.h"

using namespace std;

namespace LEX {

    Lexer::Lexer(istream &source) : source(source), currLine(1) {
        if (source.fail()) {
            throw FatalLexerError("invalid input steam. File probably does not exist.");
        }
    }

    Token Lexer::getNextToken(void) {

        char currChar;          // stores character read from stream
        currState = DFA::START; // reset state
        lexeme = "";            // reset lexeme

        stateStack = stack<int>();       // clear stack
        stateStack.push((int) DFA::BAD); // push base state

        // clear prefixed whitespace
        do {
            currChar = getNextChar();
        } while (isspace(currChar));
        source.unget(); // roll back one character

        //---------------------------------------------------//

        // Loop until a transition to the error state occurs
        while (currState != DFA::ERR) {

            // Get next character and append to lexeme
            do {
                currChar = getNextChar();
            } while (currChar == '\r');
            lexeme += currChar;

            // Clear stack if state is a final state
            if (DFA::isFinalState(currState)) {
                stateStack = stack<int>();
            }
            stateStack.push(currState);

            // state used to index table cannot be ERR due to loop condition
            currState = DFA::TRANS_TABLE[(State) currState][charCat(currChar)];
        }

        //---------------------------------------------------//

        // Loop until state popped from stack is a final state or BAD
        while (!DFA::isFinalState(currState) && currState != DFA::BAD) {

            // Pop a state and roll back one character
            currState = stateStack.top();
            stateStack.pop();
            lexeme = lexeme.substr(0, lexeme.length() - 1); // erase one character
            source.unget(); // roll back one character since an extra character was read

            // If character erased was newline, reduce currLine
            if (source.peek() == '\n') {
                currLine--;
            }
        }

        //---------------------------------------------------//

        if (DFA::isFinalState(currState)) {
            // state passed to finalStateToToken cannot be ERR since it is final state
            Token toReturn = DFA::finalStateToToken((State) currState, lexeme);
            return toReturn.getType() == TK_Comment ? getNextToken() : toReturn;
        } else {
            // Syntax error at current line
            throw LexerError_SyntaxError(currLine);
        }
    }

    int Lexer::getCurrentLine(void) const {
        return currLine;
    }

    char Lexer::getNextChar(void) {

        char toReturn;
        if (!source.eof()) {
            toReturn = (char) source.get();
            if (toReturn == '\n') currLine++;
        } else {
            // returns EOF for any further getNextChar calls
            toReturn = EOF;
        }
        return toReturn;
    }
}