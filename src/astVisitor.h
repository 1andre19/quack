#pragma once
#include "FunctionDirectory.h"
#include "SemanticCube.h"
#include "Types.h"
#include "address.h"
#include "const_table.h"
#include "instructions.h"
#include "memory_manager.h"
#include <stack>
#include <variant>

class IntegerLiteral;
class FloatingLiteral;
class StringLiteral;
class ReferenceExpr;
class BinaryOpExpr;
class UnaryOpExpr;
class CallExpr;

class AssignmentStmnt;
class VarDeclStmt;
class ParamVarDecl;
class FuncDeclStmt;
class PrintStmnt;
class WhileStmnt;
class IfStmnt;
class CallStmt;
class ReturnStmnt;

class ProgramAST;

// currently quads we manage a b t1, no virt addresses yet
struct Quadruple {
    Instruction op;
    Address arg1, arg2, result;
};

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
    virtual void visit(ReturnStmnt &node) = 0;

    // program
    virtual void visit(ProgramAST &node) = 0;
};

class QuadGenerator : public Visitor {
    FunctionDirectory &dir;
    std::vector<Quadruple> &quads;
    SemanticCube &cube;

    // type and operand tracking
    std::stack<Type> type_stack;
    std::stack<Address> argument_stack;

    // for backpatching whiles, if,
    std::stack<int> jump_stack;

    // std::stack<std::string> scope_stack;
    std::string current_scope;

    MemoryManager &mm;
    const_table &ct;

    int tmp_count = 0;

    Address new_temp();
    void emit(Instruction i, Address arg1, Address arg2, Address result);
    void backpatch(int quad_line, int quad_destination);
    SymbolEntry *lookup_symbol(const std::string &id);
    Instruction op_to_instruction(Operator op);

  public:
    QuadGenerator(FunctionDirectory &dir, std::vector<Quadruple> &quads,
                  SemanticCube &cube, MemoryManager &mm, const_table &ct)
        : dir(dir), quads(quads), current_scope("global"), cube(cube), mm(mm),
          ct(ct) {}

    // expr
    void visit(IntegerLiteral &node) override;
    void visit(FloatingLiteral &node) override;
    void visit(StringLiteral &node) override;
    void visit(ReferenceExpr &node) override;
    void visit(BinaryOpExpr &node) override;
    void visit(UnaryOpExpr &node) override;
    void visit(CallExpr &node) override;
    // stmnt
    void visit(AssignmentStmnt &node) override;
    void visit(VarDeclStmt &node) override;
    void visit(ParamVarDecl &node) override;
    void visit(FuncDeclStmt &node) override;
    void visit(PrintStmnt &node) override;
    void visit(WhileStmnt &node) override;
    void visit(IfStmnt &node) override;
    void visit(CallStmt &node) override;
    void visit(ReturnStmnt &node) override;
    // program
    void visit(ProgramAST &node) override;
};
