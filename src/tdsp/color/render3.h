#pragma once

#include <tdsp/color/color.h>

namespace tdsp {

struct Render3 {
    float min, max, scale, gamma;
    uint8_t permutation;
    char* buffer;
    size_t offset, size;
};

} // tdsp
