#include "Scopes.h"
#include <iostream>

Scope::Scope(const std::string &n, Scope *next) : name(n), next(next) {};
bool Scope::insert_symbol(const std::string &name, Type type) {
    if (vars.find(name) != vars.end()) {
        // error, we havent still decided how to handle them
        std::cerr << "symbol " << name << " already declared " << std::endl;
        return false;
    }
    vars.insert({name, SymbolEntry(name, type, false)});
    return true;
}

SymbolEntry *Scope::lookup_symbol(const std::string &name) {
    auto it = vars.find(name);
    return it != vars.end() ? &it->second : nullptr;
}

void Scope::print_table() {
    std::cout << "Vars for " << name << std::endl;
    for (auto &[key, value] : vars) {
        value.print_symbol();
    }
}

ScopeManager::ScopeManager() { currentScope = new Scope("global", nullptr); }
ScopeManager::~ScopeManager() {
    while (currentScope) {
        Scope *old = currentScope;
        currentScope = currentScope->next;
        delete old;
    }
}

void ScopeManager::enter_scope(const std::string &name) {
    Scope *sc = new Scope(name, currentScope);
    currentScope = sc;
}

// If the compiler neds to preserve the level-by-level tables for later use
// this function can leave table intact or write to external media
// and reclaim its space -- engineering a compiler keith d cooper
void ScopeManager::leave_scope() {
    Scope *old = currentScope;
    currentScope = currentScope->next;
    delete old;
}

bool ScopeManager::insert_symbol(const std::string &name, Type type) {
    if (currentScope->insert_symbol(name, type)) {
        std::cout << "Symbol of name " << name << " and type " << type
                  << " inserted" << std::endl;
        return true;
    } else {
        std::cout << "Failed to insert symbol" << std::endl;
        return false;
    }
}

SymbolEntry *ScopeManager::lookup_symbol(const std::string &name) {
    for (Scope *sc = currentScope; sc; sc = sc->next) {
        SymbolEntry *symbol = sc->lookup_symbol(name);
        if (symbol) {
            return symbol;
        }
    }
    // no symbol found in outermost scope
    std::cerr << "symbol " << name << "not found" << std::endl;
    return nullptr;
}
