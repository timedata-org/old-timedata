#pragma once

#include <fcolor/FColorList.h>

namespace fcolor {
namespace color {

FColorList tile(const FColorList&, int xMult, int yMult, int columns);

FColorList tile_pieces(
    const FColorList&, int columns, int newColumns, int newRows,
    int xCenter, int yCenter);

}  // namespace color
}  // namespace fcolor
