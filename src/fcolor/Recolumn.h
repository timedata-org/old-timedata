#pragma once

#include <fcolor/Fcolor.h>

namespace fcolor {
namespace color {

class FColorList;

void recolumn(FColorList*, int oldColumns, int newColumns);
bool mustRecolumn(int oldColumns, int newColumns);

}  // namespace color
}  // namespace fcolor
