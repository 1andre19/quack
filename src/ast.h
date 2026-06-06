#pragma once
#include "Types.h"
#include <algorithm>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Visitor;

class NodeAST {
  public:
    virtual void accept(Visitor &v) = 0;
    virtual ~NodeAST() = default;
};

class ExprAST : public NodeAST {};

class StmntAST : public NodeAST {};

class IntegerLiteral : public ExprAST {
  public:
    long Val;
    IntegerLiteral(long Val) : Val(Val) {}
    Type type = Type::INT;
    void accept(Visitor &v) override;
};

class FloatingLiteral : public ExprAST {
  public:
    double Val;
    FloatingLiteral(double Val) : Val(Val) {}
    Type type = Type::FLOAT;
    void accept(Visitor &v) override;
};

class StringLiteral : public ExprAST {
  public:
    std::string Val;
    Type type = Type::STR;
    StringLiteral(std::string Val) : Val(std::move(Val)) {}
    // type string
    void accept(Visitor &v) override;
};

// expression class for referencing a variabe
class ReferenceExpr : public ExprAST {
    // might be worth it to add types here
  public:
    std::string id;
    Type type;
    void accept(Visitor &v) override;
    ReferenceExpr(const std::string &id) : id(id) {}
};

class BinaryOpExpr : public ExprAST {
  public:
    Operator Op;
    std::unique_ptr<ExprAST> lhs; // kaleidoscope uses unique_ptr, w emay only
                                  // need refs to it well see
    std::unique_ptr<ExprAST> rhs;
    BinaryOpExpr(Operator Op, std::unique_ptr<ExprAST> lhs,
                 std::unique_ptr<ExprAST> rhs)
        : Op(Op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
    void accept(Visitor &v) override;
};

class UnaryOpExpr : public ExprAST {
  public:
    Operator Op;
    std::unique_ptr<ExprAST> rhs;
    UnaryOpExpr(Operator Op, std::unique_ptr<ExprAST> rhs)
        : Op(Op), rhs(std::move(rhs)) {}
    void accept(Visitor &v) override;
};

class AssignmentStmnt : public StmntAST {
  public:
    std::string Name;
    std::unique_ptr<ExprAST> rhs;
    AssignmentStmnt(std::string Name, std::unique_ptr<ExprAST> rhs)
        : Name(Name), rhs(std::move(rhs)) {}
    void accept(Visitor &v) override;
};

class VarDeclStmt : public StmntAST {
  public:
    std::vector<std::string> Names;
    Type type;
    VarDeclStmt(std::vector<std::string> Names, Type type)
        : Names(std::move(Names)), type(type) {}
    void accept(Visitor &v) override;
};

class ParamVarDecl : public StmntAST {
  public:
    std::string Name;
    Type type;
    ParamVarDecl(std::string Name, Type type)
        : Name(std::move(Name)), type(type) {}
    void accept(Visitor &v) override;
};

class FuncDeclStmt : public StmntAST {
  public:
    std::string Name;
    std::vector<std::unique_ptr<ParamVarDecl>>
        Params; // no need for unique_ptr, no subclasses
                // for it, but for ExprAST there is a need
    std::vector<std::unique_ptr<VarDeclStmt>> Locals;
    Type ReturnType;
    std::vector<std::unique_ptr<StmntAST>> Body;

    FuncDeclStmt(std::string Name,
                 std::vector<std::unique_ptr<ParamVarDecl>> Params,
                 std::vector<std::unique_ptr<VarDeclStmt>> Locals,
                 Type ReturnType, std::vector<std::unique_ptr<StmntAST>> Body)
        : Name(std::move(Name)), Params(std::move(Params)),
          Locals(std::move(Locals)), ReturnType(ReturnType),
          Body(std::move(Body)) {}
    void accept(Visitor &v) override;
};

// class CompoundStmnt : public StmntAST {
//     std::vector<StmntAST> Statements;
// };

class PrintStmnt : public StmntAST {
  public:
    std::vector<std::unique_ptr<ExprAST>> Args;
    PrintStmnt(std::vector<std::unique_ptr<ExprAST>> Args)
        : Args(std::move(Args)) {}
    void accept(Visitor &v) override;
};

class WhileStmnt : public StmntAST {
  public:
    std::unique_ptr<ExprAST> Condition;
    std::vector<std::unique_ptr<StmntAST>> Body;
    WhileStmnt(std::unique_ptr<ExprAST> Condition,
               std::vector<std::unique_ptr<StmntAST>> Body)
        : Condition(std::move(Condition)), Body(std::move(Body)) {}
    void accept(Visitor &v) override;
};

class IfStmnt : public StmntAST {
  public:
    std::unique_ptr<ExprAST> Condition;
    std::vector<std::unique_ptr<StmntAST>> Then;
    std::vector<std::unique_ptr<StmntAST>> Else;
    IfStmnt(std::unique_ptr<ExprAST> Condition,
            std::vector<std::unique_ptr<StmntAST>> Then,
            std::vector<std::unique_ptr<StmntAST>> Else)
        : Condition(std::move(Condition)), Then(std::move(Then)),
          Else(std::move(Else)) {}
    void accept(Visitor &v) override;
};

class CallExpr : public ExprAST {
  public:
    std::string Callee;
    std::vector<std::unique_ptr<ExprAST>> Args;
    CallExpr(const std::string &Callee,
             std::vector<std::unique_ptr<ExprAST>> Args)
        : Callee(Callee), Args(std::move(Args)) {}
    void accept(Visitor &v) override;
};

// language specification  says call statement lives under estatuto
// but calls are expressions since they can produce a value
// im prolly dumb will check later
class CallStmt : public StmntAST {
  public:
    std::unique_ptr<CallExpr> Call;
    CallStmt(std::unique_ptr<CallExpr> Call) : Call(std::move(Call)) {}
    void accept(Visitor &v) override;
};

class ProgramAST : public NodeAST {
  public:
    std::string Name;
    std::vector<std::unique_ptr<VarDeclStmt>> Globals;
    std::vector<std::unique_ptr<FuncDeclStmt>> Functions;
    std::vector<std::unique_ptr<StmntAST>> Body;

    ProgramAST(std::string Name,
               std::vector<std::unique_ptr<VarDeclStmt>> Globals,
               std::vector<std::unique_ptr<FuncDeclStmt>> Functions,
               std::vector<std::unique_ptr<StmntAST>> Body)
        : Name(std::move(Name)), Globals(std::move(Globals)),
          Functions(std::move(Functions)), Body(std::move(Body)) {}
    void accept(Visitor &v) override;
};
