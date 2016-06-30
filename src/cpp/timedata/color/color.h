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

// Everything below this point is DEPRECATED.

/** Computational base - 0..1 float or 0..255 integer?
    TODO: needs to be replaced by a Range generic type!
*/
enum class Base {normal, integer, last = integer};

template <typename Number>
struct EnumFields<RGB, Number> {
    Number red = 0, green = 0, blue = 0;

    EnumFields() = default;
    EnumFields(Number r, Number g, Number b) : red(r), green(g), blue(b) {}

    EnumFields(Color const& c) : red(c[0]), green(c[1]), blue(c[2]) {}
    operator Color() const { return {{red, green, blue}}; }
};


} // timedata
