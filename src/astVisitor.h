#pragma once
#include "ast.h"

class Visitor {
  public:
    virtual ~Visitor() = default;
    // expr
    virtual void visit(IntegerLiteral &node) = 0;
    virtual void visit(FloatingLiteral &node) = 0;
    virtual void visit(StringLiteral &node) = 0;
    virtual void visit(ReferenceExpr &node) = 0;
    virtual void visit(BinaryOpExpr &node) = 0;
    virtual void visit(UnaryOpExpr &node) = 0;
    virtual void visit(CallExpr &node) = 0;
    // stmnt
    virtual void visit(AssignmentStmnt &node) = 0;
    virtual void visit(VarDeclStmt &node) = 0;
    virtual void visit(ParamVarDecl &node) = 0;
    virtual void visit(FuncDeclStmt &node) = 0;
    virtual void visit(PrintStmnt &node) = 0;
    virtual void visit(WhileStmnt &node) = 0;
    virtual void visit(IfStmnt &node) = 0;
    virtual void visit(CallStmt &node) = 0;

    // Top-level
    virtual void visit(ProgramAST &node) = 0;
};
