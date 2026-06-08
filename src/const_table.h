#pragma once
#include "address.h"
#include <map>
#include <string>

struct const_table {
    std::map<long, int> int_consts;        //
    std::map<double, int> float_consts;    //
    std::map<std::string, int> str_consts; //

    int globals_int_count;
    int globals_float_count;
    int globals_str_count;
};
