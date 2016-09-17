#pragma once

#include <string>
#include <timedata/color/models/rgb.h>

namespace timedata {

struct Render3 {
    enum class Permutation {rgb, rbg, grb, gbr, brg, bgr};

    float gamma = 1.0f;
    uint8_t min = 0;
    uint8_t max = 255;
    float offset = 0.0f;
    Permutation permutation = Permutation::rgb;
    size_t prefix = 0; // Number of 0xff to prepad the rendering.
};

} // timedata
