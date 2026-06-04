#pragma once
#include "Types.h"

enum Instruction {
    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_GT,
    OP_LT,
    OP_EQ,
    OP_NEQ,
    MOV,
    JMP,
    JZ,
    JG,
    ERA,
    PARAM,
    CALL,
    RET,
    ENDFUNC,
    END,
    WRITE,
};

inline std::ostream &operator<<(std::ostream &out, const Instruction instr) {
    switch (instr) {
    case OP_ADD:
        out << "ADD";
        break;
    case OP_SUB:
        out << "SUB";
        break;
    case OP_MUL:
        out << "MUL";
        break;
    case OP_DIV:
        out << "DIV";
        break;
    case OP_GT:
        out << "GT";
        break;
    case OP_LT:
        out << "LT";
        break;
    case OP_EQ:
        out << "EQ";
        break;
    case OP_NEQ:
        out << "NEQ";
        break;
    case MOV:
        out << "MOV";
        break;
    case JMP:
        out << "JMP";
        break;
    case JZ:
        out << "JZ";
        break;
    case JG:
        out << "JG";
        break;
    case ERA:
        out << "ERA";
        break;
    case PARAM:
        out << "PARAM";
        break;
    case CALL:
        out << "CALL";
        break;
    case RET:
        out << "RET";
        break;
    case ENDFUNC:
        out << "ENDFUNC";
        break;
    case END:
        out << "END";
        break;
    case WRITE:
        out << "WRITE";
        break;
    }
    return out;
}
