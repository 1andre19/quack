#pragma once
#include "Types.h"
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>
class NodeAST {
  public:
    virtual ~NodeAST() = default;
};

class ExprAST : public NodeAST {};

class StmntAST : public NodeAST {};

class IntegerLiteral : public ExprAST {
    long Val;

  public:
    IntegerLiteral(long Val) : Val(Val) {}
};

class FloatingLiteral : public ExprAST {
    double Val;

  public:
    FloatingLiteral(double Val) : Val(Val) {}
};

class StringLiteral : public ExprAST {
    std::string Val;

  public:
    StringLiteral(std::string Val) : Val(std::move(Val)) {}
};

// expression class for referencing a variabe
class ReferenceExpr : public ExprAST {
    // might be worth it to add types here
    std::string Name;

  public:
    ReferenceExpr(const std::string &Name) : Name(Name) {}
};

class BinaryOpExpr : public ExprAST {
    Operator Op;
    std::unique_ptr<ExprAST> lhs; // kaleidoscope uses unique_ptr, w emay only
                                  // need refs to it well see
    std::unique_ptr<ExprAST> rhs;

  public:
    BinaryOpExpr(Operator Op, std::unique_ptr<ExprAST> lhs,
                 std::unique_ptr<ExprAST> rhs)
        : Op(Op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
};

class UnaryOpExpr : public ExprAST {
    Operator Op;
    std::unique_ptr<ExprAST> rhs;

  public:
    UnaryOpExpr(Operator Op, std::unique_ptr<ExprAST> rhs)
        : Op(Op), rhs(std::move(rhs)) {}
};

class AssignmentStmnt : public StmntAST {
    std::string Name;
    std::unique_ptr<ExprAST> rhs;

  public:
    AssignmentStmnt(std::string Name, std::unique_ptr<ExprAST> rhs)
        : Name(Name), rhs(std::move(rhs)) {}
};

class VarDeclStmt : public StmntAST {
    std::vector<std::string> Names;
    Type type;

  public:
    VarDeclStmt(std::vector<std::string> Names, Type type)
        : Names(std::move(Names)), type(type) {}
};

class ParamVarDecl : public StmntAST {
    std::string Name;
    Type type;

  public:
    ParamVarDecl(std::string Name, Type type)
        : Name(std::move(Name)), type(type) {}
};

class FuncDeclStmt : public StmntAST {
    std::string Name;
    std::vector<std::unique_ptr<ParamVarDecl>>
        Params; // no need for unique_ptr, no subclasses
                // for it, but for ExprAST there is a need
    // local vars??
    Type ReturnType;
    std::vector<std::unique_ptr<StmntAST>> Body;

  public:
    FuncDeclStmt(std::string Name,
                 std::vector<std::unique_ptr<ParamVarDecl>> Params,
                 Type ReturnType, std::vector<std::unique_ptr<StmntAST>> Body)
        : Name(std::move(Name)), Params(std::move(Params)),
          ReturnType(ReturnType), Body(std::move(Body)) {}
};

// class CompoundStmnt : public StmntAST {
//     std::vector<StmntAST> Statements;
// };

class PrintStmnt : public StmntAST {
    std::vector<std::unique_ptr<ExprAST>> Args;
    std::vector<std::string> Strings; // letrero
  public:
    PrintStmnt(std::vector<std::unique_ptr<ExprAST>> Args,
               std::vector<std::string> Strings)
        : Args(std::move(Args)), Strings(std::move(Strings)) {}
};

class WhileStmnt : public StmntAST {
    std::unique_ptr<ExprAST> Condition;
    std::vector<std::unique_ptr<StmntAST>> Body;

  public:
    WhileStmnt(std::unique_ptr<ExprAST> Condition,
               std::vector<std::unique_ptr<StmntAST>> Body)
        : Condition(std::move(Condition)), Body(std::move(Body)) {}
};

class IfStmnt : public StmntAST {
    std::unique_ptr<ExprAST> Condition;
    std::vector<std::unique_ptr<StmntAST>> Then;
    std::vector<std::unique_ptr<StmntAST>> Else;

  public:
    IfStmnt(std::unique_ptr<ExprAST> Condition,
            std::vector<std::unique_ptr<StmntAST>> Then,
            std::vector<std::unique_ptr<StmntAST>> Else)
        : Condition(std::move(Condition)), Then(std::move(Then)),
          Else(std::move(Else)) {}
};

class CallExpr : public ExprAST {
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;

  public:
    CallExpr(const std::string &Callee,
             std::vector<std::unique_ptr<ExprAST>> Args)
        : Callee(Callee), Args(std::move(Args)) {}
};

// language specification  says call statement lives under estatuto
// but calls are expressions since they can produce a value
// im prolly dumb will check later
class CallStmt : public StmntAST {
    std::unique_ptr<CallExpr> Call;

  public:
    CallStmt(std::unique_ptr<CallExpr> Call) : Call(std::move(Call)) {}
};

class ProgramAST : public NodeAST {
    std::string Name;
    std::vector<std::unique_ptr<VarDeclStmt>> Globals;
    std::vector<std::unique_ptr<FuncDeclStmt>> Functions;
    std::vector<std::unique_ptr<StmntAST>> Body;

  public:
    ProgramAST(std::string Name,
               std::vector<std::unique_ptr<VarDeclStmt>> Globals,
               std::vector<std::unique_ptr<FuncDeclStmt>> Functions,
               std::vector<std::unique_ptr<StmntAST>> Body)
        : Name(std::move(Name)), Globals(std::move(Globals)),
          Functions(std::move(Functions)), Body(std::move(Body)) {}
};
