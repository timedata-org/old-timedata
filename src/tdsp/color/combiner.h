#pragma once

#include <tdsp/base/math.h>

namespace tdsp {

struct Combiner {
    float scale, offset;

    // A bit flag - is a color component muted?
    uint mute;

    // A bit flag - is a color component inverted?
    uint invert;

    float apply(float x, uint index) const {
        static uint const flags[] = {1, 2, 4, 8, 16, 32, 64, 128};
        auto flag = flags[index];
        if (mute & flag)
            return 0;
        auto r = (x * scale) + offset;
        return (invert & flag) ? tdsp::invert(r) : r;
    }
};

} // tdsp
