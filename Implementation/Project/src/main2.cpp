#include <iostream>
#include <sstream>
#include <fstream>
#include "LEX/Lexer.h"
#include "PAR/Parser.h"
#include "General/Exceptions.h"
#include "VST/SemanticAnalysis/SemAnalysisVisitor.h"
#include "VST/InterpreterExec/InterpreterExecVisitor.h"

using namespace std;

VST::SemAnalysis::SemAnalysisVisitor semAnalysisVisitor = VST::SemAnalysis::SemAnalysisVisitor();
VST::InterpExec::InterpreterExecVisitor interpExecVisitor = VST::InterpExec::InterpreterExecVisitor();
std::vector<AST::ASTProgramNode *> trees = std::vector<AST::ASTProgramNode *>();

const string ANS_NAME = "ANS";
VST::InterpExec::Value ansValue = VST::InterpExec::Value();

int main(int argc, char *argv[]) {

    // Set initial ANS type and value
    ansValue.setVal(0);
    semAnalysisVisitor.setAnsType(ANS_NAME, ansValue.getType());
    interpExecVisitor.setAnsValue(ANS_NAME, ansValue);

    // Some notes for the user
    cout << "Note 1: Type QUIT to exit the REPL." << endl;
    cout << "Note 2: Identifier \"" << ANS_NAME << "\" is reserved." << endl;
    cout << endl;

    std::string input;
    while (true) {

        cout << "MLi> ";
        getline(cin, input);
        if (input == "QUIT") {
            break;
        } else if (input == "#st") {
            interpExecVisitor.getST()->printValues();
        } else {

            // Set up stream
            istream *source;
            if (input.length() >= 8 && input.substr(0, 7) == "#load \"" && input.at(input.length() - 1) == '\"') {
                source = new ifstream(input.substr(7, input.length() - 8), ifstream::in);
            } else {
                input += "\n"; // important for one-line comments
                source = new istringstream(input);
            }

            // Run
            AST::ASTProgramNode *tree;
            try {
                // Lexer and Parser
                LEX::Lexer lexer = LEX::Lexer(*source);
                PAR::Parser parser = PAR::Parser(lexer);;
                tree = parser.parse();
                delete source;

                // Semantic analysis and interpreter
                semAnalysisVisitor.visit(tree);
                interpExecVisitor.visit(tree);

                // Only save tree if all actions finished successfully
                trees.push_back(tree);

                // Set type and value of ANS
                VST::InterpExec::Value ans = interpExecVisitor.getLastValue();
                semAnalysisVisitor.setAnsType(ANS_NAME, ans.getType());
                interpExecVisitor.setAnsValue(ANS_NAME, ans);
                const string invertedComm = ans.getType() == String ? "\"" : "";
                cout << "Variable " << ANS_NAME << " : " << TypeNames[ans.getType()] << " = "
                     << invertedComm << ans.toString() << invertedComm << endl;

            } catch (LexerError err) {
                cout << err.what() << endl;
            } catch (ParserError err) {
                cout << err.what() << endl;
            } catch (SemAnalysisError err) {
                cout << err.what() << endl;
                delete tree; // delete if semAnalysis failed
            } catch (InterpreterError err) {
                cout << err.what() << endl;
                delete tree; // delete if interpExec failed
            }
        }
        cout << endl;
    }

    // Delete saved trees
    for (auto &tree : trees) {
        delete tree;
    }
    return 0;
}