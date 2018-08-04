#ifndef CPS2000_ASTNODE_H
#define CPS2000_ASTNODE_H

#include <string>
#include "../VST/Visitor.h"

namespace VST {

    class Visitor;
}

namespace AST {

    class ASTNode {

    public:
        virtual void Accept(VST::Visitor *v) const = 0;

        virtual ~ASTNode(void) {}
    };
}

#endif //CPS2000_ASTNODE_H
