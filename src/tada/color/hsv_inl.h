#pragma once

#include <tada/color/hsv.h>
#include <tada/color/names_inl.h>

namespace tada {

// See https://www.cs.rit.edu/~ncs/color/t_convert.html for these next two.
Color rgbToHsv(Color c) {
    auto r = std::abs(c[0]), g = std::abs(c[1]), b = std::abs(c[2]),
         v = std::max(r, std::max(g, b));
    if (not v)
        return {-1, 0, 0};

    auto delta = v - std::min(r, std::min(g, b));
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

    return {h, s, v};
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

Color rgbToHsv(Color c, Base base) {
    if (base == Base::integer)
        c = {c[0] / 255.0f, c[1] / 255.0f, c[2] / 255.0f};
    c = rgbToHsv(c);
    if (base == Base::integer)
        c = {c[0] * 255.0f, c[1] * 255.0f, c[2] * 255.0f};
    return c;
}

Color hsvToRgb(Color c, Base base) {
    if (base == Base::integer)
        c = {c[0] / 255.0f, c[1] / 255.0f, c[2] / 255.0f};
    c = hsvToRgb(c);
    if (base == Base::integer)
        c = {c[0] * 255.0f, c[1] * 255.0f, c[2] * 255.0f};
    return c;
}

} // tada
