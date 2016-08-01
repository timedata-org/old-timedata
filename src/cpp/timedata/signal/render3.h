#pragma once

#include <timedata/color/models/rgb.h>

namespace timedata {

struct Render3 {
    enum class Permutation {rgb, rbg, grb, gbr, brg, bgr};

    float gamma = 1.0f;
    uint8_t min = 0, max = 255;
    Permutation permutation = Permutation::rgb;
};

} // timedata
