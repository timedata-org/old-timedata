#pragma once

#include <memory>

#include <tdsp/Fcolor.h>

namespace tdsp {
namespace color {

class FColor;
class FColorList;

typedef void (*CombinerFunction)(FColor const&, FColor&);
using ColumnList = std::vector<int>;

enum class Combiner { XOR, ADD, SUBTRACT, MULTIPLY, DIVIDE, MIN, MAX, AND, OR };

using FColorListList = std::vector <FColorList*>;

FColorList combine(FColorListList const&, Combiner);
FColorList combine(FColorListList const&, CombinerFunction);

/** Not yet implemented. */
FColorList combine(FColorListList const&, ColumnList const& columns,
                   CombinerFunction);


CombinerFunction getCombinerFunction(std::string const&);
std::string combinerNames();

}  // namespace color
}  // namespace tdsp
