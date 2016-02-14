#pragma once

#include <cmath>
#include <utility>

#include <fcolor/Fcolor.h>

namespace fcolor {

// These functions are only good for values between 0 and pi/2.

template <typename Float>
Float fastSin(float);
Float fastCos(float);

std::pair<float, float> fastSinCos(float);

inline float restrictAngle(float x) {
    return fmod(x + M_PI, M_PI * 2) - M_PI;
}

}  // namespace fcolor
