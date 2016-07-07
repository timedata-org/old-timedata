#pragma once

#include <timedata/base/className.h>
#include <timedata/base/enum.h>
#include <timedata/base/rotate.h>
#include <timedata/signal/sample.h>

namespace timedata {

enum class RGB { red, green, blue, last = blue };

using ColorRGB = Sample<RGB>;
using ColorRGB256 = Sample<RGB, Range256<float>>;
using ColorRGB255 = Sample<RGB, Range255<float>>;

template <> inline std::string className<ColorRGB>() { return "ColorRGB"; }
template <> inline std::string className<ColorRGB255>() { return "ColorRGB255"; }
template <> inline std::string className<ColorRGB256>() { return "ColorRGB256"; }

enum class HSV { hue, saturation, value, last = value };

using ColorHSV = Sample<HSV>;
using ColorHSV256 = Sample<HSV, Range256<float>>;
using ColorHSV255 = Sample<HSV, Range255<float>>;

template <> inline std::string className<ColorHSV>() { return "ColorHSV"; }
template <> inline std::string className<ColorHSV255>() { return "ColorHSV255"; }
template <> inline std::string className<ColorHSV256>() { return "ColorHSV256"; }

template <typename Sample>
struct NormalSample {
    // TODO: conflicts with Normal, the range.
    /* Right now, we only have one family of Sample, so everything shares the
       same base and is interconvertible. */
    using normal_type = ColorRGB;
};

template <typename Sample>
using NormalType = typename NormalSample<Sample>::normal_type;

} // timedata
