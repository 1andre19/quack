#pragma once
#include "astVisitor.h"
#include "FunctionDirectory.h"
#include "SymbolEntry.h"
#include "Types.h"
#include "ast.h"
#include "custom_errors.h"
#include "instructions.h"
#include <string>
#include <variant>

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
    if (ct.int_consts.count(node.Val)) {
        argument_stack.push(ct.int_consts[node.Val]);
        return;
    }
    int addr = mm.constant_memory.new_addr(Type::INT);
    ct.int_consts[node.Val] = addr;
    argument_stack.push(addr);
};

void QuadGenerator::visit(FloatingLiteral &node) {
    type_stack.push(Type::FLOAT);
    if (ct.float_consts.count(node.Val)) {
        argument_stack.push(ct.float_consts[node.Val]);
        return;
    }
    int addr = mm.constant_memory.new_addr(Type::FLOAT);
    ct.float_consts[node.Val] = addr;
    argument_stack.push(addr);
};

void QuadGenerator::visit(StringLiteral &node) {
    type_stack.push(Type::STR);
    if (ct.str_consts.count(node.Val)) {
        argument_stack.push(ct.str_consts[node.Val]);
        return;
    }
    int addr = mm.constant_memory.new_addr(Type::STR);
    ct.str_consts[node.Val] = addr;
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

void QuadGenerator::visit(UnaryOpExpr &node) {
    node.rhs->accept(*this);

    Type expr_type = type_stack.top();
    type_stack.pop();

    Address expr_addr = argument_stack.top();
    argument_stack.pop();

    if (expr_type != Type::INT && expr_type != Type::FLOAT) {
        throw SemanticError("unary minus only works on numeric expressions");
    }

    Address zero_addr;

    if (expr_type == Type::INT) {
        if (!ct.int_consts.count(0)) {
            int addr = mm.constant_memory.new_addr(Type::INT);
            ct.int_consts[0] = addr;
        }
        zero_addr = ct.int_consts[0];
    } else {
        if (!ct.float_consts.count(0.0)) {
            int addr = mm.constant_memory.new_addr(Type::FLOAT);
            ct.float_consts[0.0] = addr;
        }
        zero_addr = ct.float_consts[0.0];
    }

    Address temp = mm.temp_memory.new_addr(expr_type);

    emit(Instruction::OP_SUB, zero_addr, expr_addr, temp);

    type_stack.push(expr_type);
    argument_stack.push(temp);
}

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
    mm.local_memory.reset_mem();
    mm.temp_memory.reset_mem();
    std::vector<FuncParam> func_params;
    Address addr;

    for (const auto &param : node.Params) {
        addr = mm.local_memory.new_addr(param->type);
        func_params.push_back({param->Name, param->type, addr});
    }

    int start_func_quad = quads.size();
    if (!dir.add_entry(node.Name, func_params, {}, node.ReturnType,
                       start_func_quad)) {
        throw SemanticError("double declaration of " + node.Name);
    }

    if (node.ReturnType != Type::VOID) {
        FunctionDirectoryEntry *global = dir.lookup_entry("global");
        Address return_addr = mm.global_memory.new_addr(node.ReturnType);
        global->add_symbol({node.Name, node.ReturnType, false, return_addr});
    }

    current_scope = node.Name;
    // std::cout << "curent scope is: " << node.Name << std::endl;

    for (auto &var : node.Locals) {
        var->accept(*this);
    }

    for (auto &stmnt : node.Body) {
        stmnt->accept(*this);
    }
    emit(Instruction::ENDFUNC, -1, -1, -1);

    // resources
    int local_int = mm.local_memory.int_size();
    int local_float = mm.local_memory.float_size();
    int local_str = mm.local_memory.str_size();
    int temp_int = mm.temp_memory.int_size();
    int temp_float = mm.temp_memory.float_size();
    int temp_str = mm.temp_memory.str_size();

    // looks kinda bad, but works now ig
    func_resources resources{local_int, local_float, local_str,
                             temp_int,  temp_float,  temp_str};

    FunctionDirectoryEntry *func_entry = dir.lookup_entry(node.Name);
    func_entry->resources = resources;
    // func_entry->print_resources();

    current_scope = "global";

    // agregar resources
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
    backpatch(jmp_to_patch,
              quads.size() + 1); // we want to jump one ahead of the
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

    // we must evaluate the arguments before, because they live in the
    // current stack_frame
    // before era was before evaluating them, so when it was called
    // args were saved in the new stack frame, which is wrong
    emit(Instruction::ERA, -1, -1, node.Callee);

    int curr_arg = node.Args.size();
    for (int i = node.Args.size() - 1; i >= 0; i--) {
        if (func->params[i].type != type_stack.top()) {
            // include expected certain type got certain type
            throw SemanticError("Invalid function call to " + node.Callee);
        }
        type_stack.pop();
        emit(Instruction::PARAM, argument_stack.top(), -1, curr_arg);
        argument_stack.pop();
        curr_arg--;
    }

    emit(Instruction::CALL, -1, -1, node.Callee);

    if (func->return_type != Type::VOID) {
        Address temp = mm.temp_memory.new_addr(func->return_type);
        // weird to not check but should notbe null pointer
        SymbolEntry *se = lookup_symbol(node.Callee);
        if (se == nullptr) {
            std::cout << "nullptr in call expr" << std::endl;
        }
        emit(Instruction::MOV, se->virt_addr, -1, temp);
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

    // change func return var
    // this directory entry should live in quadgenerator class it is used quite
    // often, no need to ask for it again and again
    // FunctionDirectoryEntry *global = dir.lookup_entry("global");

    SymbolEntry *se = lookup_symbol(curr_func->name);
    emit(Instruction::RET, se->virt_addr, -1, to_return);
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

    mm.local_memory.reset_mem();
    mm.temp_memory.reset_mem();
    for (auto &stmnt : node.Body) {
        stmnt->accept(*this);
    }
    // give symbol table the space needed for globals
    ct.globals_int_count = mm.global_memory.count_int;
    ct.globals_float_count = mm.global_memory.count_float;
    ct.globals_str_count = mm.global_memory.count_str;

    // resources for main
    int local_int = mm.local_memory.int_size();
    int local_float = mm.local_memory.float_size();
    int local_str = mm.local_memory.str_size();
    int temp_int = mm.temp_memory.int_size();
    int temp_float = mm.temp_memory.float_size();
    int temp_str = mm.temp_memory.str_size();

    func_resources resources{local_int, local_float, local_str,
                             temp_int,  temp_float,  temp_str};
    FunctionDirectoryEntry *func_entry = dir.lookup_entry("global");
    func_entry->resources = resources;
    // func_entry->print_resources();

    emit(Instruction::END, -1, -1, -1);
}
