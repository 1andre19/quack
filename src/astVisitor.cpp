#include "astVisitor.h"
#include "FunctionDirectory.h"
#include "Types.h"
#include "ast.h"
#include "custom_errors.h"
#include <string>

Address QuadGenerator::new_temp() { return "t" + std::to_string(tmp_count++); }
void QuadGenerator::emit(Operator op, Address arg1, Address arg2,
                         Address result) {
    quads.push_back({op, arg1, arg2, result});
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

void QuadGenerator::visit(IntegerLiteral &node) {
    type_stack.push(Type::INT);
    argument_stack.push(std::to_string(node.Val));
};

void QuadGenerator::visit(FloatingLiteral &node) {
    type_stack.push(Type::FLOAT);
    argument_stack.push(std::to_string(node.Val));
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
        throw SemanticError("type mismatch");
    }
    type_stack.push(res_type);
    Address arg2 = argument_stack.top();
    argument_stack.pop();
    Address arg1 = argument_stack.top();
    argument_stack.pop();
    Address temp = new_temp();

    emit(node.Op, arg1, arg2, temp);
    argument_stack.push(temp);
}

void QuadGenerator::visit(UnaryOpExpr &node) { /* todo */ }
void QuadGenerator::visit(AssignmentStmnt &node) {
    SymbolEntry *se = lookup_symbol(node.Name);
    if (se == nullptr) {
        throw SemanticError(node.Name + " undeclared");
    }
    node.rhs->accept(*this);

    Address rhs_addr = argument_stack.top();
    argument_stack.pop();
    Type rhs_type = type_stack.top();
    type_stack.pop();

    if (se->type != rhs_type) {
        throw SemanticError("type mismatch in assignment to " + node.Name);
    }
    emit(Operator::ASSIGN, rhs_addr, "-", node.Name);
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
void QuadGenerator::visit(ParamVarDecl &node) { /* todo */ }
void QuadGenerator::visit(FuncDeclStmt &node) { /* todo */ }
void QuadGenerator::visit(PrintStmnt &node) { /* todo */ }
void QuadGenerator::visit(WhileStmnt &node) { /* todo */ }
void QuadGenerator::visit(IfStmnt &node) { /* todo */ }
void QuadGenerator::visit(CallExpr &node) { /* todo */ }
void QuadGenerator::visit(CallStmt &node) { /* todo */ }
void QuadGenerator::visit(ProgramAST &node) {
    for (auto &global : node.Globals) {
        global->accept(*this);
    }
    for (auto &func : node.Functions) {
        func->accept(*this);
    }

    for (auto &stmnt : node.Body) {
        stmnt->accept(*this);
    }
}
