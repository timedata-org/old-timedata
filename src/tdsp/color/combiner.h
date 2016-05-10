#pragma once

#include <tdsp/base/math.h>

namespace tdsp {

struct Combiner {
    float scale, offset;

    // A bit flag - is a color component muted?
    uint mute;

    // A bit flag - is a color component inverted?
    uint invert;
};

inline float apply(Combiner const& combiner, float x, uint index) {
    static uint const flags[] = {1, 2, 4, 8, 16, 32, 64, 128};
    auto flag = flags[index];
    if (flag & combiner.mute)
        return 0;
    auto r = (x * combiner.scale) + combiner.offset;
    return (flag & combiner.invert) ? tdsp::invert(r) : r;
}

} // tdsp
