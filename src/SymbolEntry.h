#pragma once
#include "Types.h"
#include "address.h"
#include <iostream>
#include <string>

struct SymbolEntry {
    std::string name;
    Type type;
    bool hasBeenUsed = false;
    Address virt_addr;
    SymbolEntry(std::string n, Type t, bool h, Address addr)
        : name(n), type(t), hasBeenUsed(h), virt_addr(addr) {}
    // no use for deafult constructor of symbol entry, but i want to use [] on
    // maps
    SymbolEntry() : name(""), type(Type::ERR), hasBeenUsed(false) {}
    void print_symbol() {
        std::cout << "Symbol: " << name << " of type " << type << std::endl;
    }
};
