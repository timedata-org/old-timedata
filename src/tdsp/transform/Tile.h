#pragma once

#include <tdsp/FColorList.h>

namespace tdsp {
namespace color {

FColorList tile(const FColorList&, int xMult, int yMult, int columns);

FColorList tile_pieces(
    const FColorList&, int columns, int newColumns, int newRows,
    int xCenter, int yCenter);

}  // namespace color
}  // namespace tdsp
