#ifndef CPS2000_VISITOR_H
#define CPS2000_VISITOR_H

namespace AST {

    class ASTBinExprNode;

    class ASTFuncCallNode;

    class ASTIdentifierNode;

    class ASTSubExprNode;

    class ASTUnaryNode;

    class ASTBoolNode;

    class ASTIntNode;

    class ASTRealNode;

    class ASTStringNode;

    class ASTActualParamsNode;

    class ASTFormalParamNode;

    class ASTFormalParamsNode;

    class ASTAssignNode;

    class ASTBlockNode;

    class ASTFuncDeclNode;

    class ASTIfNode;

    class ASTPrintNode;

    class ASTReturnNode;

    class ASTVarDeclNode;

    class ASTWhileNode;

    class ASTProgramNode;
}

namespace VST {

    class Visitor {

    public:
        virtual ~Visitor(void) {}

        virtual void visit(const AST::ASTProgramNode *node) = 0;

        virtual void visit(const AST::ASTBinExprNode *node) = 0;

        virtual void visit(const AST::ASTSubExprNode *node) = 0;

        virtual void visit(const AST::ASTBoolNode *node) = 0;

        virtual void visit(const AST::ASTIntNode *node) = 0;

        virtual void visit(const AST::ASTRealNode *node) = 0;

        virtual void visit(const AST::ASTStringNode *node) = 0;

        virtual void visit(const AST::ASTUnaryNode *node) = 0;

        virtual void visit(const AST::ASTIdentifierNode *node) = 0;

        virtual void visit(const AST::ASTFuncCallNode *node) = 0;

        virtual void visit(const AST::ASTActualParamsNode *node) = 0;

        virtual void visit(const AST::ASTVarDeclNode *node) = 0;

        virtual void visit(const AST::ASTAssignNode *node) = 0;

        virtual void visit(const AST::ASTPrintNode *node) = 0;

        virtual void visit(const AST::ASTIfNode *node) = 0;

        virtual void visit(const AST::ASTWhileNode *node) = 0;

        virtual void visit(const AST::ASTReturnNode *node) = 0;

        virtual void visit(const AST::ASTFuncDeclNode *node) = 0;

        virtual void visit(const AST::ASTFormalParamsNode *node) = 0;

        virtual void visit(const AST::ASTFormalParamNode *node) = 0;

        virtual void visit(const AST::ASTBlockNode *node) = 0;
    };
}

#endif //CPS2000_VISITOR_H
