#pragma once
#include "astVisitor.h"
#include "FunctionDirectory.h"
#include "Types.h"
#include "ast.h"
#include "custom_errors.h"
#include "instructions.h"
#include <string>

Address QuadGenerator::new_temp() { return "t" + std::to_string(tmp_count++); }
void QuadGenerator::emit(Instruction i, Address arg1, Address arg2,
                         Address result) {
    quads.push_back({i, arg1, arg2, result});
}

void QuadGenerator::backpatch(int line_to_patch, int quad_destination) {
    Quadruple &to_patch = quads[line_to_patch];
    to_patch.result = std::to_string(quad_destination);
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
    argument_stack.push(std::to_string(node.Val));
};

void QuadGenerator::visit(FloatingLiteral &node) {
    type_stack.push(Type::FLOAT);
    argument_stack.push(std::to_string(node.Val));
};

void QuadGenerator::visit(StringLiteral &node) {
    type_stack.push(Type::STR);
    argument_stack.push(node.Val);
};

void QuadGenerator::visit(ReferenceExpr &node) {
    SymbolEntry *sym = lookup_symbol(node.id);
    if (sym == nullptr) {
        // var not declared
        throw SemanticError({node.id + " is undeclared"});
    }
    node.type = sym->type;
    type_stack.push(node.type);
    argument_stack.push(node.id);
};

void QuadGenerator::visit(BinaryOpExpr &node) {
    node.lhs->accept(*this);
    node.rhs->accept(*this);

    // no need for which type is left or right
    // i think...
    //, but might aswell just in case
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
    Address temp = new_temp();

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
    emit(Instruction::MOV, rhs_addr, "-", node.Name);
}

void QuadGenerator::visit(VarDeclStmt &node) {
    FunctionDirectoryEntry *curr = dir.lookup_entry(current_scope);
    for (const auto &name : node.Names) {
        SymbolEntry sym = SymbolEntry(name, node.type, false);
        if (!curr->add_symbol(SymbolEntry(sym))) {
            throw SemanticError("double declaration of " + name);
        }
    }
}

void QuadGenerator::visit(ParamVarDecl &node) {}
void QuadGenerator::visit(FuncDeclStmt &node) {
    std::vector<FuncParam> func_params;
    for (const auto &param : node.Params) {
        func_params.push_back({param->Name, param->type});
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
    emit(Instruction::ENDFUNC, "-", "-", "-");
    current_scope = "global";
}
void QuadGenerator::visit(PrintStmnt &node) {
    for (auto &arg : node.Args) {
        arg->accept(*this);
        Address to_print = argument_stack.top();
        argument_stack.pop();
        type_stack.pop();
        emit(Instruction::WRITE, "-", "-", to_print);
    }
}
void QuadGenerator::visit(WhileStmnt &node) { /* todo */ }
void QuadGenerator::visit(IfStmnt &node) { /* todo */ }
void QuadGenerator::visit(CallExpr &node) { /* todo */ }
void QuadGenerator::visit(CallStmt &node) { /* todo */ }
void QuadGenerator::visit(ProgramAST &node) {
    emit(Instruction::JMP, "-", "-", "-");
    for (auto &global : node.Globals) {
        global->accept(*this);
    }
    for (auto &func : node.Functions) {
        func->accept(*this);
    }

    for (auto &stmnt : node.Body) {
        stmnt->accept(*this);
    }
    emit(Instruction::END, "-", "-", "-");
}
