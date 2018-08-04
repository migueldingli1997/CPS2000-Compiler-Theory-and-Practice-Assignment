#include <iostream>
#include <fstream>
#include "LEX/Lexer.h"
#include "PAR/Parser.h"
#include "VST/PrintXml/PrintXmlVisitor.h"
#include "VST/SemanticAnalysis/SemAnalysisVisitor.h"
#include "General/Exceptions.h"
#include "VST/InterpreterExec/InterpreterExecVisitor.h"

using namespace std;

int main(int argc, char *argv[]) {

    if (argc == 3) {

        AST::ASTProgramNode *tree;
        try {
            //----------------------------------------------------------------------//
            // Lexer and Parser                                                     //
            //----------------------------------------------------------------------//

            ifstream source = ifstream(argv[1], ifstream::in);

            LEX::Lexer lexer = LEX::Lexer(source);
            PAR::Parser parser = PAR::Parser(lexer);
            tree = parser.parse();

            source.close();
            cout << "Lexer and Parser were successful." << endl;

            //----------------------------------------------------------------------//
            // XML Output                                                           //
            //----------------------------------------------------------------------//

            ofstream output = ofstream(string(argv[2]));
            VST::PrintXml::PrintXmlVisitor xmlVisitor = VST::PrintXml::PrintXmlVisitor(output);
            xmlVisitor.visit(tree);

            output.close();
            cout << "XML print was successful." << endl;

            //----------------------------------------------------------------------//
            // Semantic Analysis                                                    //
            //----------------------------------------------------------------------//

            VST::SemAnalysis::SemAnalysisVisitor().visit(tree);
            cout << "Semantic Analysis was successful." << endl;

            //----------------------------------------------------------------------//
            // Interpreter Execution                                                //
            //----------------------------------------------------------------------//

            cout << "Any output during execution is shown below..." << endl;
            cout << "---------------------------------------------" << endl;
            VST::InterpExec::InterpreterExecVisitor().visit(tree);
            cout << "---------------------------------------------" << endl;
            cout << "Interpreter Execution Pass was successful." << endl;

            delete tree;

        } catch (ParserError err) {
            cout << err.what() << endl;
        } catch (LexerError err) {
            cout << err.what() << endl;
        } catch (XmlVisitorError err) {
            cout << err.what() << endl;
            delete tree; // delete if printXML failed
        } catch (SemAnalysisError err) {
            cout << err.what() << endl;
            delete tree; // delete if interpExec failed
        } catch (InterpreterError err) {
            cout << err.what() << endl;
            delete tree; // delete if interpExec failed
        }
    } else {
        cout << "Please insert source file path (input) and XML file path (output)." << endl;
    }
    return 0;
}