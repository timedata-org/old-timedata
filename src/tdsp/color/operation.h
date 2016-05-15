#pragma once

#include <string>
#include <vector>

#include <tdsp/color/colorList.h>

namespace tdsp {
namespace operation {

enum class Unary {ABS, CLEAR, INVERT, NEGATE, size};
enum class Binary {ADD, DIV, MAX, MIN, MUL, POW, SUB, size};
enum class Side {LEFT, RIGHT, size};

void run(Unary, ColorList&);

template <typename X>
void run(Binary, Side, X const&, ColorList&);

template <typename X, typename Y>
void run(Binary, Side, X const&, Y const&, ColorList&);

} // operation
} // tdsp
