#pragma once
#include "astVisitor.h"
#include "FunctionDirectory.h"
#include "Types.h"
#include "ast.h"
#include "custom_errors.h"
#include "instructions.h"
#include <string>

void QuadGenerator::emit(Instruction i, Address arg1, Address arg2,
                         Address result) {
    quads.push_back({i, arg1, arg2, result});
}

void QuadGenerator::backpatch(int line_to_patch, int quad_destination) {
    Quadruple &to_patch = quads[line_to_patch];
    to_patch.result = quad_destination;
}

SymbolEntry *QuadGenerator::lookup_symbol(const std::string &id) {
    FunctionDirectoryEntry *func = dir.lookup_entry(current_scope);
    auto it = func->symbol_table.find(id);
    if (it != func->symbol_table.end()) {
        return &it->second;
    }

    FunctionDirectoryEntry *global = dir.lookup_entry("global");
    auto it_glob = global->symbol_table.find(id);
    if (it_glob != global->symbol_table.end()) {
        return &it_glob->second;
    }

    return nullptr;
}

Instruction QuadGenerator::op_to_instruction(Operator op) {
    switch (op) {
    case Operator::PLUS:
        return OP_ADD;
    case Operator::MINUS:
        return OP_SUB;
    case Operator::TIMES:
        return OP_MUL;
    case Operator::DIV:
        return OP_DIV;
    case Operator::GT:
        return OP_GT;
    case Operator::LT:
        return OP_LT;
    case Operator::EQ:
        return OP_EQ;
    case Operator::NEQ:
        return OP_NEQ;
    default:
        throw std::runtime_error("operator has no instruction");
    }
}

void QuadGenerator::visit(IntegerLiteral &node) {
    type_stack.push(Type::INT);
    Address addr = mm.constant_memory.new_addr(Type::INT);
    argument_stack.push(addr);
};

void QuadGenerator::visit(FloatingLiteral &node) {
    type_stack.push(Type::FLOAT);
    Address addr = mm.constant_memory.new_addr(Type::FLOAT);
    argument_stack.push(addr);
};

void QuadGenerator::visit(StringLiteral &node) {
    type_stack.push(Type::STR);
    Address addr = mm.constant_memory.new_addr(Type::STR);
    argument_stack.push(addr);
};

void QuadGenerator::visit(ReferenceExpr &node) {
    SymbolEntry *sym = lookup_symbol(node.id);
    if (sym == nullptr) {
        // var not declared
        throw SemanticError({node.id + " is undeclared"});
    }
    node.type = sym->type;
    type_stack.push(node.type);
    argument_stack.push(sym->virt_addr);
};

void QuadGenerator::visit(BinaryOpExpr &node) {
    node.lhs->accept(*this);
    node.rhs->accept(*this);

    // no need for which type is left or right
    //, but just in case
    Type arg2_type = type_stack.top();
    type_stack.pop();
    Type arg1_type = type_stack.top();
    type_stack.pop();
    // todo: change all name methods to snake_case
    Type res_type = cube.CheckType(node.Op, arg1_type, arg2_type);

    if (res_type == Type::ERR) {
        // no fcking clue as in idk how to handle it, its type mismatch
        throw SemanticError("type mismatch; ");
    }

    type_stack.push(res_type);
    Address arg2 = argument_stack.top();
    argument_stack.pop();
    Address arg1 = argument_stack.top();
    argument_stack.pop();
    Address temp = mm.temp_memory.new_addr(res_type);

    emit(op_to_instruction(node.Op), arg1, arg2, temp);
    argument_stack.push(temp);
}

void QuadGenerator::visit(UnaryOpExpr &node) { /* todo */ }

void QuadGenerator::visit(AssignmentStmnt &node) {
    SymbolEntry *se = lookup_symbol(node.Name);
    if (se == nullptr) {
        throw SemanticError(node.Name + " is undeclared");
    }
    node.rhs->accept(*this);

    Address rhs_addr = argument_stack.top();
    argument_stack.pop();
    Type rhs_type = type_stack.top();
    type_stack.pop();

    if (se->type != rhs_type) {
        throw SemanticError("type mismatch in assignment to " + node.Name +
                            "; ");
    }
    emit(Instruction::MOV, rhs_addr, -1, se->virt_addr);
}

void QuadGenerator::visit(VarDeclStmt &node) {
    FunctionDirectoryEntry *curr = dir.lookup_entry(current_scope);
    for (const auto &name : node.Names) {
        // missing addr
        int addr;
        if (curr->name == "global") {
            addr = mm.global_memory.new_addr(node.type);
        } else {
            addr = mm.local_memory.new_addr(node.type);
        }
        SymbolEntry sym = SymbolEntry(name, node.type, false, addr);
        if (!curr->add_symbol(SymbolEntry(sym))) {
            throw SemanticError("double declaration of " + name);
        }
    }
}

void QuadGenerator::visit(ParamVarDecl &node) {}
void QuadGenerator::visit(FuncDeclStmt &node) {
    std::vector<FuncParam> func_params;
    // fucked up
    Address addr;

    for (const auto &param : node.Params) {
        addr = mm.local_memory.new_addr(param->type);
        func_params.push_back({param->Name, param->type, addr});
    }

    if (!dir.add_entry(node.Name, func_params, node.ReturnType)) {
        throw SemanticError("double declaration of " + node.Name);
    }
    current_scope = node.Name;
    std::cout << "curent scope is: " << node.Name << std::endl;

    for (auto &var : node.Locals) {
        var->accept(*this);
    }

    for (auto &stmnt : node.Body) {
        stmnt->accept(*this);
    }
    emit(Instruction::ENDFUNC, -1, -1, -1);
    current_scope = "global";
    mm.local_memory.reset_mem();
    mm.temp_memory.reset_mem();
}
void QuadGenerator::visit(PrintStmnt &node) {
    for (auto &arg : node.Args) {
        arg->accept(*this);
        Address to_print = argument_stack.top();
        argument_stack.pop();
        type_stack.pop();
        emit(Instruction::WRITE, -1, -1, to_print);
    }
}
void QuadGenerator::visit(WhileStmnt &node) {
    node.Condition->accept(*this);
    jump_stack.push(quads.size() - 1);

    Address condition = argument_stack.top();
    argument_stack.pop();
    emit(Instruction::JZ, condition, -1, -1); // will need backpatching
    jump_stack.push(quads.size() - 1);

    for (auto &stmnt : node.Body) {
        stmnt->accept(*this);
    }

    int jmp_to_patch = jump_stack.top();
    jump_stack.pop();
    backpatch(jmp_to_patch, quads.size()); // we want to jump one ahead of the
                                           // goto that brings us back to while
    int start_while = jump_stack.top();
    jump_stack.pop();
    emit(Instruction::JMP, -1, -1, start_while);
}

void QuadGenerator::visit(IfStmnt &node) {
    // todo,
    // todo
    // todo
    int if_jmp;

    node.Condition->accept(*this);
    Address condition = argument_stack.top();
    argument_stack.pop();
    emit(Instruction::JZ, condition, -1, -1);
    jump_stack.push(quads.size() - 1);

    for (auto &stmnt : node.Then) {
        stmnt->accept(*this);
    }

    if (node.Else.empty()) {
        if_jmp = jump_stack.top();
        jump_stack.pop();
        backpatch(if_jmp, quads.size());
        return;
    }
    // jump to skip the else branch
    emit(Instruction::JMP, -1, -1, -1);

    // we need to tell if jmp where to go in case of false
    if_jmp = jump_stack.top();
    jump_stack.pop();
    backpatch(if_jmp, quads.size());

    jump_stack.push(quads.size() - 1);

    for (auto &stmnt : node.Else) {
        stmnt->accept(*this);
    }
    int else_jmp = jump_stack.top();
    jump_stack.pop();
    backpatch(else_jmp,
              quads.size()); // maybe we could make quads.size() be instruction
                             // no or line no, quads.size is a bit confusing
}

void QuadGenerator::visit(CallExpr &node) {
    FunctionDirectoryEntry *func = dir.lookup_entry(node.Callee);
    if (func == nullptr) {
        throw SemanticError("function " + node.Callee + " does not exist");
    }
    emit(Instruction::ERA, -1, -1, node.Callee);

    if (node.Args.size() != func->params.size()) {
        throw SemanticError("Invalid function call to " + node.Callee +
                            ": incorrect number of arguments, got: " +
                            std::to_string(node.Args.size()) + " expected: " +
                            std::to_string(func->params.size()));
    }
    /*
    compute args ex: func(a : entero, b : flotante, c + 10 : entero)
     on the stack they will live as
     c + 10
     b
     a
     and type stack:
     entero
     flot
     enero
     FuncDirEntry has vector of FuncParam,
     iterate over this from end to start,
     compare with type stack, to see if the order of args are correct
    */

    for (auto &arg : node.Args) {
        arg->accept(*this);
    }

    int curr_arg = node.Args.size();
    for (int i = node.Args.size() - 1; i >= 0; i--) {
        if (func->params[i].type != type_stack.top()) {
            // include expected certain type got certain type
            throw SemanticError("Invalid function call to " + node.Callee);
        }
        type_stack.pop();
        emit(Instruction::PARAM, argument_stack.top(), -1,
             std::to_string(curr_arg));
        argument_stack.pop();
        curr_arg--;
    }

    emit(Instruction::CALL, -1, -1, node.Callee);

    if (func->return_type != Type::VOID) {
        Address temp = mm.temp_memory.new_addr(func->return_type);
        emit(Instruction::MOV, node.Callee, -1, temp);
        argument_stack.push(temp);
        type_stack.push(func->return_type);
    }
}

void QuadGenerator::visit(CallStmt &node) { node.Call->accept(*this); }

void QuadGenerator::visit(ReturnStmnt &node) {
    node.expr->accept(*this);
    FunctionDirectoryEntry *curr_func = dir.lookup_entry(current_scope);
    if (type_stack.top() != curr_func->return_type) {
        throw SemanticError("incorrect return type for function " +
                            curr_func->name + " ; expected type lallalal");
    }
    type_stack.pop();
    Address to_return = argument_stack.top();
    argument_stack.pop();
    emit(Instruction::RET, -1, -1, to_return);
}

void QuadGenerator::visit(ProgramAST &node) {
    emit(Instruction::JMP, -1, -1, -1); // jump to main
    for (auto &global : node.Globals) {
        global->accept(*this);
    }
    for (auto &func : node.Functions) {
        func->accept(*this);
    }

    // patch jmp to main
    backpatch(0, quads.size());

    for (auto &stmnt : node.Body) {
        stmnt->accept(*this);
    }
    emit(Instruction::END, -1, -1, -1);
}
