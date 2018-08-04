#ifndef CPS2000_EXCEPTIONS_H
#define CPS2000_EXCEPTIONS_H

#include <exception>
#include <stdexcept>
#include "Type.h"

class NormalError : public std::runtime_error {
public:
    NormalError(const std::string &);
};

class FatalError : public std::runtime_error {
public:
    FatalError(const std::string &);
};

// ---------------------------------- NORMAL ERRORS ----------------------------------

class LexerError : public NormalError {
public:
    LexerError(const std::string &);
};

class ParserError : public NormalError {
public:
    ParserError(const std::string &);
};

class XmlVisitorError : public NormalError {
public:
    XmlVisitorError(const std::string &__arg);
};

class SemAnalysisError : public NormalError {
public:
    SemAnalysisError(const std::string &);
};

class InterpreterError : public NormalError {
public:
    InterpreterError(const std::string &);
};

// ---------------------------------- FATAL ERRORS ----------------------------------

class FatalTypeError : public FatalError {
public:
    FatalTypeError(const std::string &);
};

class FatalLexerError : public FatalError {
public:
    FatalLexerError(const std::string &);
};

class FatalParserError : public FatalError {
public:
    FatalParserError(const std::string &);
};

class FatalXmlVisitorError : public FatalError {
public:
    FatalXmlVisitorError(const std::string &__arg);
};

class FatalSymbolTableError : public FatalError {
public:
    FatalSymbolTableError(const std::string &);
};

class FatalSemAnalysisError : public FatalError {
public:
    FatalSemAnalysisError(const std::string &);
};

class FatalValueError : public FatalError {
public:
    FatalValueError(const std::string &__arg);
};

class FatalInterpreterError : public FatalError {
public:
    FatalInterpreterError(const std::string &);
};

// ---------------------------------- SPECIFIC ERRORS ----------------------------------

class LexerError_SyntaxError : public LexerError {
public:
    LexerError_SyntaxError(const int line);
};

class ParserError_SyntaxError : public ParserError {
public:
    ParserError_SyntaxError(const int line, const std::string cause);
};

class SemAnalysisError_TypeMismatch : public SemAnalysisError {
public:
    SemAnalysisError_TypeMismatch(const std::string expected, const std::string found, const std::string situation);
    SemAnalysisError_TypeMismatch(const Type expected, const Type found, const std::string situation);
};

class FatalValueError_TriedToGetValueOfUnexpectedType : public FatalValueError {
public:
    FatalValueError_TriedToGetValueOfUnexpectedType();
};

#endif //CPS2000_EXCEPTIONS_H
