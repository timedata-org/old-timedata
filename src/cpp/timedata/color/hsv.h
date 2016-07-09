#pragma once

#include <timedata/color/rgb.h>
#include <timedata/signal/convert.h>

namespace timedata {

enum class HSV { hue, saturation, value, last = value };

using ColorHSV = Sample<HSV>;
using ColorHSV256 = Sample<HSV, Range256<float>>;
using ColorHSV255 = Sample<HSV, Range255<float>>;

template <> inline std::string className<ColorHSV>() { return "ColorHSV"; }
template <> inline std::string className<ColorHSV255>() { return "ColorHSV255"; }
template <> inline std::string className<ColorHSV256>() { return "ColorHSV256"; }

namespace converter {

// See: https://www.cs.rit.edu/~ncs/color/t_convert.html
// http://codeitdown.com/hsl-hsb-hsv-color/

template <>
inline void convertSample(ColorRGB const& in, ColorHSV& out) {
    auto red = *in[RGB::red];
    auto green = *in[RGB::green];
    auto blue = *in[RGB::blue];

    auto& hue = *out[HSV::hue];
    auto& saturation = *out[HSV::saturation];
    auto& value = *out[HSV::value];

    value = std::max({red, green, blue});
    if (not value) {
        out.clear();
        return;
    }

    auto delta = value - std::min({red, green, blue});
    saturation = delta / value;
    if (value == red)
        hue = (green - blue) / delta;          // Between yellow and magenta.
    else if (value == green)
        hue = 2.0f + (blue - red) / delta;     // Between cyan and yellow.
    else
        hue = 4.0f + (red - green) / delta;    // Between magenta and cyan.

    hue /= 6.0f;
    if (hue < 0.0f)
        hue += 1.0f;
}

template <>
inline void convertSample(ColorHSV const& in, ColorRGB& out) {
    auto& hue = *in[HSV::hue];
    auto& saturation = *in[HSV::saturation];
    auto& value = *in[HSV::value];

    if (not saturation) {
        out.fill(value);
        return;
    }
    auto h = hue * 6.0f;            // sector 0 to 5
    auto sector = static_cast<int>(h);
    auto f = h - sector;

    auto a = [&]() { return value * (1.0f - saturation); };
    auto b = [&]() { return value * (1.0f - saturation * f); };
    auto c = [&]() { return value * (1.0f - saturation * (1.0f - f)); };
    auto d = [&]() {
        switch (sector) {
            case 0:  return ColorRGB{value, c(), a()};
            case 1:  return ColorRGB{b(), value, a()};
            case 2:  return ColorRGB{a(), value, c()};
            case 3:  return ColorRGB{a(), b(), value};
            case 4:  return ColorRGB{c(), a(), value};
            default: return ColorRGB{value, a(), b()};
        }
    };
    out = d();
}

} // converter
} // timedata
