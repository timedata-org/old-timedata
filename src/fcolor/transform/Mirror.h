#pragma once

#include <fcolor/FColorList.h>

namespace fcolor {
namespace color {

FColorList mirror(
    const FColorList&, unsigned int x, unsigned int y,
    bool reverseX, bool reverseY);

}  // namespace color
}  // namespace fcolor
