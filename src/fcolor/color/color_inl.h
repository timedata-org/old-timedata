#pragma once

#include <limits>
#include <fcolor/base/number_inl.h>
#include <fcolor/base/level_inl.h>

#include <fcolor/color/color.h>

namespace fcolor {

template <typename Number>
void clear(Color<Number>& c) {
    c.red = c.green = c.blue = 0;
}

template <typename Number, typename Alpha>
void clear(Color<Number, Alpha>& c) {
    c.red = c.green = c.blue = 0;
    c.alpha = level::maximum<Alpha>();
}

template <typename T>
T clear() {
    T result;
    clear(result);
    return result;
}

template <typename Number, typename Alpha, typename Scalar>
Color<Number, Alpha> operator*(Color<Number, Alpha> const& c, Scalar r) {
    auto color = c;
    color.red *= r;
    color.green *= r;
    color.blue *= r;
    return color;
}

template <typename Number, typename Alpha, typename Scalar>
Color<Number, Alpha> operator/(Color<Number, Alpha> const& c, Scalar r) {auto color = c;
    color.red /= r;
    color.green /= r;
    color.blue /= r;
    return color;
}

template <typename Number, typename Alpha, typename Scalar>
Color<Number, Alpha> operator*(Scalar r, Color<Number, Alpha> const& c) {
    return c * r;
}

template <class Color>
Color red() {
    auto c = clear<Color>();
    c.red = level::maximum<typename Color::number_t>();
    return c;
}

template <class Color>
Color green() {
    auto c = clear<Color>();
    c.green = level::maximum<typename Color::number_t>();
    return c;
}

template <class Color>
Color blue() {
    auto c = clear<Color>();
    c.blue = level::maximum<typename Color::number_t>();
    return c;
}

template <typename N1, typename A1, typename N2>
Color<N2> convert(Color<N1> const& c) {
    return {convert<N2>(c.red), convert<N2>(c.green), convert<N2>(c.blue)};
}

template <typename N1, typename A1, typename N2, typename A2=A1>
Color<N2> convert(Color<N1> const& c) {
    return {convert<N2>(c.red), convert<N2>(c.green), convert<N2>(c.blue),
            convert<A2>(c.alpha)};
}

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
Float<Number> colorfulness2(Color<Number, Alpha> const& color) {
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

/** Apply a one-argument function to each component in a Color. */
template <typename Color, typename Function>
void applyToComponents(Color& color, Function f) {
    color.red = f(color.red);
    color.green = f(color.green);
    color.blue = f(color.blue);
}

template <typename Color, typename Function>
void combineComponents(Color& c, Color const& x, Color const& y, Function f) {
    c.red = f(x.red, y.red);
    c.green = f(x.green, y.green);
    c.blue = f(x.blue, y.blue);
}

template <typename Color, typename Float>
void interpolate(Color& c, Color const& begin, Color const& end, Float r) {
    using Number = typename Color::number_t;
    combineComponents(c, begin, end, [=] (Number b, Number e) {
        return level::convert<Number>(Float(b) + r * (Float(e) - Float(b)));
    });
}

#if 0

template <typename Color, typename Function>
Color applyToComponents(Function op, Color const& color) {
    auto c = color;
    c.red = op(c.red);
    c.green = op(c.green);
    c.blue = op(c.blue);
    return c;
}

template <typename Color, typename Function>
Color applyToComponents(Function op, Color const& x, Color const& y) {
    auto c = x;
    c.red = op(x.red, y.red);
    c.green = op(x.green, y.green);
    c.blue = op(x.blue, y.blue);
    return c;
}

template <typename Number, typename Alpha, typename Function>
Color<Number, Alpha> applyToComponentsWithAlpha(
        Function f, Color<Number, Alpha> const& color) {
    auto c = applyToComponents(op, color);
    c.alpha = op(color.alpha);
    return c;
}

template <typename Number, typename Function>
Color<Number> applyToComponentsWithAlpha(
        Function op, Color<Number> const& color) {
    return applyToComponents(op, color);
}

template <typename Number, typename Alpha, typename Function>
Color<Number, Alpha> applyToComponentsWithAlpha(
        Function op,
        Color<Number, Alpha> const& x,
        Color<Number, Alpha> const& y) {
    auto c = applyToComponents(op, x, y);
    c.alpha = op(x.alpha, y.alpha);
    return c;
}

template <typename Number, typename Alpha, typename Function>
Color<Number> applyToComponentsWithAlpha(
        Function op,
        Color<Number> const& x,
        Color<Number> const& y) {
    return applyToComponents(op, x, y);
}

template <typename Number, typename Float>
Color<Number> interpolate(
          Color<Number> const& x, Color<Number> const& y, Float ratio) {
    return applyToComponents(
        [&] (Number cx, Number cy) {
            return cx + ratio * (cy - cx);
        }, x, y);
}


/** Apply a one-argument function to each component in a Color. */
template <typename Color, typename Function>
Color applyToComponents(Function, Color const&);

/** Apply a two-argument function to each component in two Colors. */
template <typename Color, typename Function>
Color applyToComponents(Function, Color const&, Color const&);

/** Apply a one-argument function to each component in a Color, and
    the alpha channel, if any. */
template <typename Color, typename Function>
Color applyToComponentsWithAlpha(Function, Color const&);

/** Apply a two-argument function to each component in two Colors, and
    the alpha channel, if any. */
template <typename Color, typename Function>
Color applyToComponentsWithAlpha(Function, Color const&, Color const&);

/** Interpolate between two colors. */
template <typename Number, typename Float>
Color<Number> interpolate(Color<Number> const&, Color<Number> const&, Float);

/** Apply a one-argument function to each component in a Color, and
    the alpha channel, if any. */
template <typename Color, typename Function>
void applyToComponentsWithAlpha(Color&, Function);

/** Apply a one-argument function to each component in a Color. */
template <typename Color, typename Function>
void applyToComponents(Color&, Function);

#endif
}  // namespace fcolor
