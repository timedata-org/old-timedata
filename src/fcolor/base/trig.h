#pragma once

#include <cmath>
#include <utility>
#include <fcolor/base/number.h>

namespace fcolor {

// These fast, approximate functions are only good for values between 0 and pi/2.
// TODO: either junk or test these.

template <typename Float>
Float fastSin(Float);

template <typename Float>
Float fastCos(Float);

template <typename Float>
Pair<Float> fastSinCos(Float);

template <typename Float>
Float restrictAngle(Float);

}  // namespace fcolor
