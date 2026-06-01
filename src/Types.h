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

inline std::ostream &operator<<(std::ostream &out, const Operator op) {
    switch (op) {
    case PLUS:
        out << "+";
        break;
    case MINUS:
        out << "-";
        break;
    case TIMES:
        out << "*";
        break;
    case DIV:
        out << "/";
        break;
    case GT:
        out << ">";
        break;
    case LT:
        out << "<";
        break;
    case NEQ:
        out << "!=";
        break;
    case EQ:
        out << "==";
        break;
    case ASSIGN:
        out << "=";
        break;
    case OP_COUNT:
        out << "OP_COUNT";
        break;
    }
    return out;
}
