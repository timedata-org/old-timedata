#pragma once

#include <tdsp/color/color.h>

namespace tdsp {

struct Render3 {
    enum class Permutation {rgb, rbg, grb, gbr, brg, bgr};

    float min = 0, max = 255, scale = 1, gamma = 1;
    uint8_t permutation = 0;
    // Permutation permutation = Permutation::rgb;
    size_t offset = 0, size = 0;

    float operator()(float s) const {
        s = std::min(1.0f, std::max(0.0f, scale * s));
        if (gamma != 1)
            s = pow(s, gamma);
        return std::min(max, min + (max - min + 1) * s);
    }

    using PermArray = std::array<uint8_t, 3>;
    using PermsArray = EnumArray<PermArray, Permutation>;
};

} // tdsp
