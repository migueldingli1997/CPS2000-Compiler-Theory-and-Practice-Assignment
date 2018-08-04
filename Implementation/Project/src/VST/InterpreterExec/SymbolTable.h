#ifndef PROJECT_SYMBOLTABLE_H
#define PROJECT_SYMBOLTABLE_H

#include <string>
#include <map>
#include "../../AST/ASTPARAM/ASTFormalParamsNode.h"
#include "Value.h"
#include "../SemanticAnalysis/SymbolTable.h"

namespace VST {
    namespace InterpExec {

        using namespace std;

        typedef struct SymbolTableValue {
            const Value value;
            const AST::ASTFormalParamsNode *formalParams;
        } SymbolTableValue;

        typedef std::map<const std::string, const SymbolTableValue> scope;

        class SymbolTable {

        private:
            std::vector<scope> scopes;

        public:
            SymbolTable(void);

            virtual ~SymbolTable(void);

            void push(void);

            void pop(void);

            void insert(const std::string key, const Value value);

            void insert(const std::string key, const Value value, const AST::ASTFormalParamsNode *formalParams);

            void modify(const std::string key, const Value value);

            void modify(const std::string key, const Value value, const AST::ASTFormalParamsNode *formalParams);

            int lookup(const std::string key) const;

            SymbolTableValue getValue(const std::string key) const;

            void printValues(void) const;
        };
    }
}

#endif //PROJECT_SYMBOLTABLE_H
