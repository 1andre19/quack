#pragma once

#include "SymbolEntry.h"
#include "Types.h"
#include "address.h"
#include "func_resources.h"
#include <string>
#include <unordered_map>
#include <vector>

struct FuncParam {
    std::string id;
    Type type;
    Address virt_addr;
};

class FunctionDirectoryEntry {
  public:
    std::string name;
    std::vector<FuncParam> params;
    func_resources resources;
    Type return_type;
    int start_quad;
    std::unordered_map<std::string, SymbolEntry> symbol_table;
    FunctionDirectoryEntry(std::string name,
                           const std::vector<FuncParam> params,
                           func_resources resources, Type type, int start_quad)
        : name(name), params(params), resources(resources), return_type(type),
          start_quad(start_quad) {
        // populate func symb table with params
        for (const auto &param : params) {
            symbol_table[param.id] =
                SymbolEntry(param.id, param.type, false, param.virt_addr);
        }
    }

    bool add_symbol(SymbolEntry sym) {
        if (symbol_table.count(sym.name)) {
            return false;
        }
        symbol_table[sym.name] = sym;
        return true;
    }

    void print_resources();
};

// could not a class but just an object of type map<str, funcEntry>
class FunctionDirectory {
  public:
    std::unordered_map<std::string, FunctionDirectoryEntry> directory;
    bool add_entry(const std::string &funcName,
                   const std::vector<FuncParam> &params,
                   func_resources resources, Type return_type, int start_quad);
    FunctionDirectoryEntry *lookup_entry(const std::string &name);
};
