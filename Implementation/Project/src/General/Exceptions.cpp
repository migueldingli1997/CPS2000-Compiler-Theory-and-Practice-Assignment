#include <iostream>
#include "Exceptions.h"

NormalError::NormalError(const std::string &msg) :
        runtime_error(msg) {}

FatalError::FatalError(const std::string &msg) :
        runtime_error("FATAL " + msg) {}

// ------------------------------------------------------------ GENERAL NORMAL ERRORS

LexerError::LexerError(const std::string &msg) :
        NormalError("Lexer error :: " + msg) {}

ParserError::ParserError(const std::string &msg) :
        NormalError("Parser error :: " + msg) {}

XmlVisitorError::XmlVisitorError(const std::string &msg) :
        NormalError("XML Visitor error :: " + msg) {}

SemAnalysisError::SemAnalysisError(const std::string &msg) :
        NormalError("Semantic analysis error :: " + msg) {}

InterpreterError::InterpreterError(const std::string &msg) :
        NormalError("Interpreter error :: " + msg) {}

// ------------------------------------------------------------ GENERAL FATAL ERRORS

FatalTypeError::FatalTypeError(const std::string &msg) :
        FatalError("Type error :: " + msg) {}

FatalLexerError::FatalLexerError(const std::string &msg) :
        FatalError("Lexer error :: " + msg) {}

FatalParserError::FatalParserError(const std::string &msg) :
        FatalError("Parser error :: " + msg) {}

FatalXmlVisitorError::FatalXmlVisitorError(const std::string &msg) :
        FatalError("XML Visitor error :: " + msg) {}

FatalSymbolTableError::FatalSymbolTableError(const std::string &msg) :
        FatalError("Symbol table error :: " + msg) {}

FatalSemAnalysisError::FatalSemAnalysisError(const std::string &msg) :
        FatalError("Semantic analysis error :: " + msg) {}

FatalValueError::FatalValueError(const std::string &msg) :
        FatalError("Value error :: " + msg) {}

FatalInterpreterError::FatalInterpreterError(const std::string &msg) :
        FatalError("Interpreter error :: " + msg) {}

// ------------------------------------------------------------ SPECIFIC ERRORS

LexerError_SyntaxError::LexerError_SyntaxError(const int line) :
        LexerError("syntax error at line " + std::to_string(line) + ".") {}

ParserError_SyntaxError::ParserError_SyntaxError(const int line, const std::string cause) :
        ParserError("syntax error at line " + std::to_string(line) + " due to " + cause + ".") {}

SemAnalysisError_TypeMismatch::SemAnalysisError_TypeMismatch(const std::string expected, const std::string found,
                                                             const std::string situation) :
        SemAnalysisError("type mismatch; expected \"" + expected + "\" " +
                         "but found \"" + found + "\" in " + situation + ".") {}

SemAnalysisError_TypeMismatch::SemAnalysisError_TypeMismatch(const Type expected, const Type found,
                                                             const std::string situation) :
        SemAnalysisError_TypeMismatch(TypeNames[expected], TypeNames[found], situation) {}

FatalValueError_TriedToGetValueOfUnexpectedType::FatalValueError_TriedToGetValueOfUnexpectedType() :
        FatalValueError("tried to get a value of an unexpected type.") {}