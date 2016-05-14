#pragma once

#include <string>
#include <vector>

#include <tdsp/color/colorList.h>

namespace tdsp {

struct Operation {
    enum class Unary {ABS, CLEAR, INVERT, NEGATE, size};
    enum class Binary {ADD, DIV, MAX, MIN, MUL, POW, SUB, size};
};

void run(Operation::Unary, ColorList&);

void runLeft(Operation::Binary, float, ColorList&);
void runLeft(Operation::Binary, ColorList const&, ColorList&);

void runRight(Operation::Binary, float, ColorList&);
void runRight(Operation::Binary, ColorList const&, ColorList&);

} // tdsp
