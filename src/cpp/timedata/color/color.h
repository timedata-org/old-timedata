#pragma once

#include <timedata/base/enum.h>
#include <timedata/base/rotate.h>
#include <timedata/signal/sample.h>

namespace timedata {

enum class RGB { red, green, blue, last = blue };
enum class RGBW { red, green, blue, white, last = white };
enum class HSB { hue, saturation, brightness, last = brightness };

using Color = Sample<RGB, Normal<float>>;
using Color256 = Sample<RGB, EightBit<float>>;
using Color255 = Sample<RGB, Range255<float>>;

} // timedata
