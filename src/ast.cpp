#include "ast.h"
#include "astVisitor.h"

void IntegerLiteral::accept(Visitor &v) { v.visit(*this); }
void FloatingLiteral::accept(Visitor &v) { v.visit(*this); }
void StringLiteral::accept(Visitor &v) { v.visit(*this); }
void ReferenceExpr::accept(Visitor &v) { v.visit(*this); }
void BinaryOpExpr::accept(Visitor &v) { v.visit(*this); }
void UnaryOpExpr::accept(Visitor &v) { v.visit(*this); }
void AssignmentStmnt::accept(Visitor &v) { v.visit(*this); }
void VarDeclStmt::accept(Visitor &v) { v.visit(*this); }
void ParamVarDecl::accept(Visitor &v) { v.visit(*this); }
void FuncDeclStmt::accept(Visitor &v) { v.visit(*this); }
void PrintStmnt::accept(Visitor &v) { v.visit(*this); }
void WhileStmnt::accept(Visitor &v) { v.visit(*this); }
void IfStmnt::accept(Visitor &v) { v.visit(*this); }
void CallExpr::accept(Visitor &v) { v.visit(*this); }
void CallStmt::accept(Visitor &v) { v.visit(*this); }
void ProgramAST::accept(Visitor &v) { v.visit(*this); }
void ReturnStmnt::accept(Visitor &v) { v.visit(*this); }
