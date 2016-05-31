#pragma once

#include <tada/base/enum.h>
#include <tada/base/rotate.h>
#include <tada/signal/signal.h>

namespace tada {

enum class RGB { red, green, blue, last = blue };
enum class RGBW { red, green, blue, white, last = white };
enum class HSB { hue, saturation, brightness, last = brightness };
// enum class Stereo { left, right };

using Color = Sample<RGB>;
using Color256 = Sample<RGB, uint8_t>;

struct ColorS {
    float red = 0, green = 0, blue = 0;

    ColorS() = default;
    ColorS(float r, float g, float b) : red(r), green(g), blue(b) {}
    ColorS(Color const& c) : red(c[0]), green(c[1]), blue(c[2]) {}

    operator Color() const { return {{red, green, blue}}; }
};

inline ColorS rotate(ColorS c, int positions) {
    Color co = c;
    rotate(co, positions);
    return co;
}

inline void minInto(ColorS const& in, ColorS& out) {
    out.red = std::min(in.red, out.red);
    out.green = std::min(in.green, out.green);
    out.blue = std::min(in.blue, out.blue);
}

inline void maxInto(ColorS const& in, ColorS& out) {
    out.red = std::max(in.red, out.red);
    out.green = std::max(in.green, out.green);
    out.blue = std::max(in.blue, out.blue);
}

inline float cmp(ColorS const& x, ColorS const& y) {
    if (auto d = x.red - y.red)
        return d;
    if (auto d = x.green - y.green)
        return d;
    return x.blue - y.blue;
}

inline float distance2(Color const& x, Color const& y) {
    auto dr = x[0] - y[0], dg = x[1] - y[1], db = x[2] - y[2];
    return dr * dr + dg * dg + db * db;
}

inline float distance(Color const& x, Color const& y) {
    return sqrt(distance2(x, y));
}

/** Computational base - 0..1 float or 0..255 integer? */
enum class Base {normal, integer, last = integer};



} // tada
