#pragma once

#include <tdsp/FColorList.h>

namespace tdsp {
namespace color {

FColorList mirror(
    const FColorList&, unsigned int x, unsigned int y,
    bool reverseX, bool reverseY);

}  // namespace color
}  // namespace tdsp
