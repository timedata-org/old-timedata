#pragma once

#include <timedata/base/math.h>

namespace timedata {

struct Combiner {
    float scale, offset;

    // A bit flag - is a color component muted?
    uint mute;

    // A bit flag - is a color component inverted?
    uint invert;

    float operator()(float x, uint i) const {
        static uint const flags[] = {1, 2, 4, 8, 16, 32, 64, 128};
        if (int(i) >= std::end(flags) - std::begin(flags))
            log("bad flags", i, flags);
        else if (flags[i] & mute)
            return 0;
        auto r = (x * scale) + offset;
        return (flags[i] & invert) ? timedata::invert(r) : r;
    }
};

} // timedata
