#pragma once
#include "Types.h"

struct MemorySegment {
    int base_int;
    int base_float;
    int base_str;

    int count_int = 0;
    int count_float = 0;
    int count_str = 0;

    void reset_mem() {
        count_int = 0;
        count_float = 0;
        count_str = 0;
    };

    int new_addr(Type type) {
        switch (type) {
        case Type::FLOAT:
            return base_float + count_float++;
        case Type::INT:
            return base_int + count_int++;
        case Type::STR:
            return base_str + count_str++;
        default:
            return 0;
        }
    };

    int int_size() { return count_int; }
    int float_size() { return count_float; }
    int str_size() { return count_str; }
};

class MemoryManager {
  public:
    MemorySegment global_memory{1000, 2500, 5000};
    MemorySegment local_memory{7500, 10000, 12500};
    MemorySegment temp_memory{15000, 17500, 20000};
    MemorySegment constant_memory{22500, 25000, 27500};
};
