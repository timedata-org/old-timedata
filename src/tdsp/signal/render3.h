#pragma once

#include <tdsp/color/color.h>

namespace tdsp {

struct Render3 {
    float min = 0, max = 255, scale = 1, gamma = 1;
    uint8_t permutation = 0;
    size_t offset = 0, size = 0;
};

} // tdsp
