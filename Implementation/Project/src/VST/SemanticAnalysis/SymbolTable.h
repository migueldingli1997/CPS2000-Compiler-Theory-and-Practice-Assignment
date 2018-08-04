#ifndef CPS2000_SYMBOLTABLE_H
#define CPS2000_SYMBOLTABLE_H

#include <map>
#include <vector>
#include "../../General/Type.h"

#define NOTFOUND 0
#define INNERMOST 1

namespace AST {

    class ASTIdentifierNode;

    class ASTFormalParamsNode;
}

namespace VST {
    namespace SemAnalysis {

        typedef struct SymbolTableValue {
            const Type type;
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

            void insert(const std::string key, const Type type);

            void insert(const std::string key, const Type type, const AST::ASTFormalParamsNode *formalParams);

            void modify(const std::string key, const Type type);

            void modify(const std::string key, const Type type, const AST::ASTFormalParamsNode *formalParams);

            int lookup(const std::string key) const;

            SymbolTableValue getValue(const std::string key) const;
        };
    }
}

#endif //CPS2000_SYMBOLTABLE_H
