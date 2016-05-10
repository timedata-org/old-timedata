#pragma once

#include <tdsp/base/enum.h>
#include <tdsp/signal/signal.h>

namespace tdsp {

enum class RGB { red, green, blue, size };
enum class RGBW { red, green, blue, white, size };
enum class HSB { hue, saturation, brightness, size };
// enum class Stereo { left, right };

using Color = Sample<RGB>;
using Color256 = Sample<RGB, uint8_t>;

inline Color makeColor(float r, float g, float b) {
    return {{r, g, b}};
}

} // tdsp
