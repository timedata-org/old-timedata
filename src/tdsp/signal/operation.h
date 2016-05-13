#pragma once

#include <string>
#include <vector>

#include <tdsp/color/color.h>

namespace tdsp {

struct Operation {
    enum class Unary {ABS, CLEAR, INVERT, NEGATE, size};
    enum class Commutative {ADD, MAX, MIN, MUL, size};
    enum class NonCommutative {DIV, SUB, POW, size};
};

} // tdsp
