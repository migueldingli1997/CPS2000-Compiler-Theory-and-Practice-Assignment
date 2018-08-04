#include <iostream>
#include "SymbolTable.h"
#include "../../General/Exceptions.h"
#include "../../AST/ASTPARAM/ASTFormalParamNode.h"
#include "../../AST/ASTEXPR/ASTIdentifierNode.h"
#include "../../AST/ASTSTMT/ASTFuncDeclNode.h"

namespace VST {
    namespace InterpExec {

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

        void SymbolTable::insert(const string key, const Value value) { insert(key, value, nullptr); }

        void SymbolTable::insert(const string key, const Value value, const AST::ASTFormalParamsNode *formalParams) {

            SymbolTableValue stVal = {value, formalParams};
            scope &topScope = scopes.back();
            if (topScope.find(key) == topScope.end()) {
                topScope.insert(scope::value_type(key, stVal));
            } else {
                throw FatalSymbolTableError("key already exists.");
            }
        }

        void SymbolTable::modify(const string key, const Value value) {
            modify(key, value, nullptr);
        }

        void SymbolTable::modify(const string key, const Value value, const AST::ASTFormalParamsNode *formalParams) {

            const int scopeCount = lookup(key);
            if (scopeCount == NOTFOUND) {
                throw FatalSymbolTableError("identifier does not exist.");
            }
            SymbolTableValue stVal = {value, formalParams};
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

        void SymbolTable::printValues(void) const {

            for (auto &stValue : scopes.at(0)) {
                if (stValue.second.formalParams == nullptr) {
                    const string invertedComm = stValue.second.value.getType() == String ? "\"" : "";
                    cout << "Variable " << stValue.first
                         << " : " << TypeNames[stValue.second.value.getType()]
                         << " = " << invertedComm << stValue.second.value.toString() << invertedComm << endl;
                } else {
                    cout << "Function " << stValue.first << "(";
                    const vector<const AST::ASTFormalParamNode *> *params = &stValue.second.formalParams->getParams();
                    for (int i = 0; i < params->size(); i++) {
                        const AST::ASTFormalParamNode *param = params->at(i);
                        cout << param->getIdentifier()->getStr() << " : " << TypeNames[param->getType()];
                        if (i < params->size() - 1) {
                            cout << ", ";
                        }
                    }
                    cout << ") : " << TypeNames[stValue.second.value.getFunctionVal()->getType()] << endl;
                }
            }
        }
    }
}
