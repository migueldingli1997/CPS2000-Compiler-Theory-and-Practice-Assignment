#include "Value.h"
#include "../../General/Exceptions.h"

namespace VST {
    namespace InterpExec {

        using namespace std;

        Type Value::getType(void) const { return valueType; }

        std::string Value::toString(void) const {

            switch (valueType) {
                case Real:
                    return to_string(theValue.theReal);
                case Bool:
                    return (theValue.theBool ? "true" : "false");
                case Int:
                    return to_string(theValue.theInt);
                case String:
                    return *theValue.theString;
                default:
                    throw FatalValueError("unhandled type.");
            }
        }

        void Value::setVal(const double val) {

            theValue.theReal = val;
            valueType = Real;
        }

        void Value::setVal(const bool val) {

            theValue.theBool = val;
            valueType = Bool;
        }

        void Value::setVal(const int val) {

            theValue.theInt = val;
            valueType = Int;
        }

        void Value::setVal(const string val) {

            theValue.theString = new string(val);
            valueType = String;
        }

        void Value::setVal(const AST::ASTFuncDeclNode *functionNode) {

            theValue.theFunction = functionNode;
            valueType = NUMBER_OF_TYPES; // NUMBER_OF_TYPES used to represent function
        }

        void Value::validateGet(const Type typeToGet) const {

            if (valueType != typeToGet) {
                throw FatalValueError_TriedToGetValueOfUnexpectedType();
            }
        }

        double Value::getRealVal(void) const {

            validateGet(Real);
            return theValue.theReal;
        }

        bool Value::getBoolVal(void) const {

            validateGet(Bool);
            return theValue.theBool;
        }

        int Value::getIntVal(void) const {

            validateGet(Int);
            return theValue.theInt;
        }

        string Value::getStringVal(void) const {

            validateGet(String);
            string toReturn = theValue.theString->data();
            delete theValue.theString;
            return toReturn;
        }

        const AST::ASTFuncDeclNode *Value::getFunctionVal(void) const {

            // NUMBER_OF_TYPES used to represent function
            validateGet(NUMBER_OF_TYPES);
            return theValue.theFunction;
        }

        double Value::getNumericVal(void) {

            if (valueType == Int) {
                return theValue.theInt;
            } else if (valueType == Real) {
                return theValue.theReal;
            } else {
                throw FatalValueError_TriedToGetValueOfUnexpectedType();
            }
        }
    }
}