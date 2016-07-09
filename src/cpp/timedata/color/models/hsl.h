#pragma once

#include <timedata/color/models/hsv.h>
#include <timedata/signal/convert.h>

namespace timedata {

enum class HSL { hue, saturation, lightness, last = lightness };

using ColorHSL = Sample<HSL>;
template <> inline std::string className<ColorHSL>() { return "ColorHSL"; }

namespace converter {

// See: http://codeitdown.com/hsl-hsb-hsl-color/

template <>
inline void convertSample(ColorHSV const& in, ColorHSL& out) {
    auto hue = *in[HSV::hue];
    auto saturation = *in[HSV::saturation];
    auto value = *in[HSV::value];

    auto lightness = value * (2 - saturation) / 2;
    auto divisor = 1 - std::abs(2 * lightness - 1);

    out[HSL::hue] = hue;
    out[HSL::lightness] = lightness;
    out[HSL::saturation] = value * saturation / divisor;
}

template <>
inline void convertSample(ColorHSL const& in, ColorHSV& out) {
    auto hue = *in[HSL::hue];
    auto saturation = *in[HSL::saturation];
    auto lightness = *in[HSL::lightness];

    auto value = (2 * lightness +
                  saturation * (1 - std::abs(2 * lightness - 1))) / 2;
    out[HSV::hue] = hue;
    out[HSV::saturation] = 2 * (value - lightness) / value;
    out[HSV::value] = value;
}

template <>
inline void convertSample(ColorRGB const& in, ColorHSL& out) {
    ColorHSV hsv;
    convertSample(in, hsv);
    convertSample(hsv, out);
}

template <>
inline void convertSample(ColorHSL const& in, ColorRGB& out) {
    ColorHSV hsv;
    convertSample(in, hsv);
    convertSample(hsv, out);
}

} // converter
} // timedata
