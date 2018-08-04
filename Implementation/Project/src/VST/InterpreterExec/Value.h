#ifndef PROJECT_VALUETABLE_H
#define PROJECT_VALUETABLE_H

#include <string>
#include "../../General/Type.h"

namespace AST {

    class ASTFuncDeclNode;
}

namespace VST {
    namespace InterpExec {

        typedef union AnyValue {
            double theReal;
            bool theBool;
            int theInt;
            std::string *theString;
            const AST::ASTFuncDeclNode *theFunction;
        } AnyValue;

        class Value {

        private:
            AnyValue theValue;
            Type valueType;

            void validateGet(const Type typeToGet) const;

        public:
            Type getType(void) const;

            std::string toString(void) const;

            //-------------------------------------

            void setVal(const double val);

            void setVal(const bool val);

            void setVal(const int val);

            void setVal(const std::string val);

            void setVal(const AST::ASTFuncDeclNode *functionNode);

            //-------------------------------------

            double getRealVal(void) const;

            bool getBoolVal(void) const;

            int getIntVal(void) const;

            std::string getStringVal(void) const;

            const AST::ASTFuncDeclNode *getFunctionVal(void) const;

            double getNumericVal(void);
        };
    }
}

#endif //PROJECT_VALUETABLE_H
