#pragma once
#include "Types.h"
#include <iostream>
#include <string>

struct SymbolEntry {
    std::string name;
    Type type;
    bool hasBeenUsed = false;
    // int virtAddr
    SymbolEntry(std::string n, Type t, bool h)
        : name(n), type(t), hasBeenUsed(h) {}
    void print_symbol() {
        std::cout << "Symbol: " << name << " of type " << type << std::endl;
    }
};
