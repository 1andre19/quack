#pragma once
#include <ostream>
#include <string>

enum Type {
    INT,
    FLOAT,
    VOID,
    ERR,
    // TYPE_COUNT,
};

const int TYPE_COUNT = 2; // for now, we really only do have 2 real types

enum Operator {
    PLUS,
    MINUS,
    TIMES,
    DIV,
    GT,
    LT,
    NEQ,
    EQ,
    ASSIGN,
    OP_COUNT,
};

inline std::ostream &operator<<(std::ostream &out, const Type t) {
    switch (t) {
    case INT:
        out << "INT";
        break;
    case FLOAT:
        out << "FLOAT";
        break;
    case VOID:
        out << "VOID";
        break;
    case ERR:
        out << "ERR";
        break;
    }
    return out;
}
