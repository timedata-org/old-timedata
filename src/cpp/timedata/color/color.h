#pragma once

#include <timedata/base/className.h>
#include <timedata/base/enum.h>
#include <timedata/base/rotate.h>
#include <timedata/signal/sample.h>

namespace timedata {

enum class RGB { red, green, blue, last = blue };
enum class HSB { hue, saturation, brightness, last = brightness };

template <> inline std::string className<RGB>() { return "RGB"; }
template <> inline std::string className<HSB>() { return "HSB"; }

using Color = Sample<RGB, Normal<float>>;
using Color256 = Sample<RGB, EightBit<float>>;
using Color255 = Sample<RGB, Range255<float>>;

template <> inline std::string className<Color>() { return "RGBColor"; }
template <> inline std::string className<Color255>() { return "RGBColor255"; }
template <> inline std::string className<Color256>() { return "RGBColor256"; }

} // timedata
