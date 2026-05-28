#pragma once

#include "Types.h"

class SemanticCube {
  public:
    SemanticCube();
    Type CheckType(Operator op, Type left, Type right) const;

  private:
    Type cube[OP_COUNT][TYPE_COUNT][TYPE_COUNT];
    // ops + - / *
    // int float
    // return float if any side is float

    // ops > < != ==
    // always return an int

    void CubeInit();
};
