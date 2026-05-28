#pragma once

#include "SymbolEntry.h"

#include <string>
#include <unordered_map>

class Scope {
  public:
    Scope(const std::string &name, Scope *next);

    bool insert_symbol(const std::string &name, Type type);
    SymbolEntry *lookup_symbol(const std::string &name);

    Scope *next;
    void print_table();

  private:
    std::string name;
    std::unordered_map<std::string, SymbolEntry> vars;
};

class ScopeManager {
  public:
    ScopeManager();
    ~ScopeManager();

    void enter_scope(const std::string &name);
    void leave_scope();

    bool insert_symbol(const std::string &name, Type type);
    SymbolEntry *lookup_symbol(const std::string &name);
    Scope *currentScope;

  private:
};
