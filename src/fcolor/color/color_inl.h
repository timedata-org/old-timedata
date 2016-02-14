#pragma once

#include <limits>
#include <fcolor/color/color.h>
#include <fcolor/base/number_inl.h>
#include <fcolor/base/level_inl.h>

namespace fcolor {

template <typename Number, typename Alpha>
Float<Number> distance2(Color<Number, Alpha> const& x,
                        Color<Number, Alpha> const& y) {
    /* Using all these local variables guarantees that we don't get
       numeric overflow when performing the intermediate calculations! */
    Float<Number>
        xr = x.red,
        xg = x.green,
        xb = x.blue,

        yr = y.red,
        yg = y.green,
        yb = y.blue,

        dr = xr - yr,
        dg = xg - yg,
        db = xb - yb;
    return dr * dr + dg * dg + db + db;
}

/** Return the sum of the squares of the color differences. */
template <typename Number, typename Alpha>
Float<Number> greyness2(Color<Number, Alpha> const& color) {
    Float<Number>
        r = color.red,
        g = color.green,
        b = color.blue,
        rg = r - g,
        gb = g - b,
        br = b - r;
    return rg * rg + gb * gb + br * br;
}

template <typename Number, typename Alpha>
Color<Number> withoutAlpha(Color<Number, Alpha> c) {
    return {c.red, c.green, c.blue};
}

template <typename Number, typename Alpha>
Color<Number, Alpha> withAlpha(Color<Number> c, Alpha alpha) {
    return {c.red, c.green, c.blue, alpha};
}

template <typename Color, typename Operator>
Color applyToComponents(Operator op, Color const& color) {
    auto c = color;
    c.red = op(c.red);
    c.green = op(c.green);
    c.blue = op(c.blue);
    return c;
}

template <typename Color, typename Operator>
Color applyToComponents(Operator op, Color const& x, Color const& y) {
    auto c = x;
    c.red = op(x.red, y.red);
    c.green = op(x.green, y.green);
    c.blue = op(x.blue, y.blue);
    return c;
}

template <typename Number, typename Alpha, typename Float>
Color<Number, Alpha> interpolate(Color<Number, Alpha> const& x,
                                 Color<Number, Alpha> const& y, Float ratio) {
    return applyToComponents(
        [&] (Number cx, Number cy) { return cx + ratio * (cy - cx); }, x, y);
}

}  // namespace fcolor
