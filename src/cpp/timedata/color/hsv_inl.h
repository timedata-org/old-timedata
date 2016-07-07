#pragma once

#include <timedata/color/hsv.h>
#include <timedata/color/names_inl.h>

namespace timedata {

// See https://www.cs.rit.edu/~ncs/color/t_convert.html for these next two.

template <>
inline void convertSample(ColorRGB const& in, ColorHSV& out) {
    auto& r = in[RGB::red];
    auto& g = in[RGB::red];
    auto& b = in[RGB::red];
    auto v = std::max({r, g, b});
    if (not v) {
        out.clear();
        return;
    }

    auto delta = v - std::min({r, g, b});
    auto s = delta / v;
    float h;
    if (r == v)
        h = (g - b) / delta;        // between yellow & magenta
    else if (g == v)
        h = 2 + (b - r) / delta;    // between cyan & yellow
    else
        h = 4 + (r - g) / delta;    // between magenta & cyan
    h /= 6;
    if (h < 0)
        h += 1;

    out = {h, s, v};
}

Color hsvToRgb(Color c) {
    auto h = std::abs(c[0]), s = std::abs(c[1]), v = std::abs(c[2]);
    if (not s)
        return {v, v, v};
    h *= 6;            // sector 0 to 5
    auto sector = static_cast<int>(h);
    auto f = h - sector;
    auto p = [&]() { return v * (1 - s); };
    auto q = [&]() { return v * (1 - s * f); };
    auto t = [&]() { return v * (1 - s * (1 - f)); };
    switch (sector) {
        case 0:  return {v, t(), p()};
        case 1:  return {q(), v, p()};
        case 2:  return {p(), v, t()};
        case 3:  return {p(), q(), v};
        case 4:  return {t(), p(), v};
        default: return {v, p(), q()};
    }
}

} // timedata
