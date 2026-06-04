#pragma once

#include "SymbolEntry.h"
#include "Types.h"
#include <string>
#include <unordered_map>
#include <vector>

struct FuncParam {
    std::string id;
    Type type;
};

class FunctionDirectoryEntry {
  public:
    std::string name;
    std::vector<FuncParam> params;
    // std::size_t resources
    Type return_type;
    // int start_address; for quads
    std::unordered_map<std::string, SymbolEntry> symbol_table;
    FunctionDirectoryEntry(std::string name,
                           const std::vector<FuncParam> params, Type type)
        : name(name), params(params), return_type(type) {
        // populate func symb table with params
        for (const auto &param : params) {
            symbol_table[param.id] = SymbolEntry(param.id, param.type, false);
        }
    }

    bool add_symbol(SymbolEntry sym) {
        if (symbol_table.count(sym.name)) {
            return false;
        }
        symbol_table[sym.name] = sym;
        return true;
    }
};

// could not a class but just an object of type map<str, funcEntry>
class FunctionDirectory {
    std::unordered_map<std::string, FunctionDirectoryEntry> directory;

  public:
    bool add_entry(const std::string &funcName,
                   const std::vector<FuncParam> &params, Type return_type);
    FunctionDirectoryEntry *lookup_entry(const std::string &name);
};
