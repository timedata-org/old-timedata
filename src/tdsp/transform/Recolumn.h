#pragma once

#include <tdsp/Fcolor.h>

namespace tdsp {
namespace color {

class FColorList;

void recolumn(FColorList*, int oldColumns, int newColumns);
bool mustRecolumn(int oldColumns, int newColumns);

}  // namespace color
}  // namespace tdsp
