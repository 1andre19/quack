#include "SemanticCube.h"

SemanticCube::SemanticCube() { CubeInit(); }
Type SemanticCube::CheckType(Operator op, Type left, Type right) const {
    if (left == Type::ERR || right == Type::ERR) {
        return Type::ERR;
    }
    return cube[op][left][right];
}

void SemanticCube::CubeInit() {
    for (int i = 0; i < OP_COUNT; i++) {
        for (int j = 0; j < TYPE_COUNT; j++) {
            for (int k = 0; k < TYPE_COUNT; k++) {
                cube[i][j][k] = Type::ERR;
            }
        }
    }

    for (int op = 0; op <= DIV; op++) {
        cube[op][Type::INT][Type::INT] = Type::INT;
        cube[op][Type::INT][Type::FLOAT] = Type::FLOAT;
        cube[op][Type::FLOAT][Type::INT] = Type::FLOAT;
        cube[op][Type::FLOAT][Type::FLOAT] = Type::FLOAT;
    }

    for (int op = DIV + 1; op <= EQ; op++) {
        cube[op][Type::INT][Type::INT] = Type::INT;
        cube[op][Type::INT][Type::FLOAT] = Type::INT;
        cube[op][Type::FLOAT][Type::INT] = Type::INT;
        cube[op][Type::FLOAT][Type::FLOAT] = Type::INT;
    }

    cube[Operator::ASSIGN][Type::INT][Type::INT] = Type::INT;
    cube[Operator::ASSIGN][Type::FLOAT][Type::FLOAT] = Type::INT;
}
