#include <iostream>
#include "SymbolTable.h"
#include "../../General/Exceptions.h"

namespace VST {
    namespace SemAnalysis {

        using namespace std;

        SymbolTable::SymbolTable(void) {
            push(); // Start of global scope
        }

        SymbolTable::~SymbolTable(void) {

            // There may be more than one scope if error caused early termination
            while(scopes.size() > 0) {
                scopes.pop_back();
            }
        }

        void SymbolTable::push(void) {
            scopes.push_back(scope());
        }

        void SymbolTable::pop(void) {

            if (scopes.size() > 1) {
                scopes.pop_back();
            } else {
                throw FatalSymbolTableError("tried to pop global scope.");
            }
        }

        void SymbolTable::insert(const string key, const Type type) { insert(key, type, nullptr); }

        void SymbolTable::insert(const string key, const Type type, const AST::ASTFormalParamsNode *formalParams) {

            SymbolTableValue value = {type, formalParams};
            scope &topScope = scopes.back();
            if (topScope.find(key) == topScope.end()) {
                topScope.insert(scope::value_type(key, value));
            } else {
                throw FatalSymbolTableError("key already exists.");
            }
        }

        void SymbolTable::modify(const string key, const Type type) {
            modify(key, type, nullptr);
        }

        void SymbolTable::modify(const string key, const Type type, const AST::ASTFormalParamsNode *formalParams) {

            const int scopeCount = lookup(key);
            if (scopeCount == NOTFOUND) {
                throw FatalSymbolTableError("identifier does not exist.");
            }
            SymbolTableValue stVal = {type, formalParams};
            scopes.at(scopes.size() - scopeCount).erase(key); // erase previous key-value pair
            scopes.at(scopes.size() - scopeCount).insert(scope::value_type(key, stVal)); // add new key-value pair
        }

        int SymbolTable::lookup(const string key) const {

            // Iterate from innermost scope to outermost scope
            int scopeCount = INNERMOST;
            vector<scope>::const_reverse_iterator scope;
            for (scope = scopes.rbegin(); scope != scopes.rend(); ++scope) {
                if (scope->find(key) != scope->end()) {
                    return scopeCount;
                }
                scopeCount++;
            }
            return NOTFOUND;
        }

        SymbolTableValue SymbolTable::getValue(const string key) const {

            const int scopeCount = lookup(key);
            if (scopeCount == NOTFOUND) {
                throw FatalSymbolTableError("identifier does not exist.");
            }
            return scopes.at(scopes.size() - scopeCount).at(key);
        }
    }
}
