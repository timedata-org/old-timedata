#pragma once

#include <string>
#include <vector>

#include <tdsp/color/colorList.h>

namespace tdsp {
namespace operation {

enum class Unary {ABS, CLEAR, INVERT, NEGATE, last = NEGATE};
enum class Binary {ADD, DIV, MAX, MIN, MUL, POW, SUB, last = SUB};
enum class Side {LEFT, RIGHT, last = RIGHT};

void runInto(Unary, ColorList& out);

void runTogether(Unary, ColorList const& in, ColorList& out);

void runInto(Binary, Side, float, ColorList&);
void runInto(Binary, Side, ColorList const&, ColorList&);

void runTogether(Binary, Side, ColorList const&, float, ColorList&);
void runTogether(Binary, Side, ColorList const&, ColorList const&, ColorList&);

} // operation
} // tdsp
