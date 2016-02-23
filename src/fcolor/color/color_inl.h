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

template <typename Color, typename Function>
auto componentApplier(Function f) {
    return [=](Color& to, Color const& from) {
        to.red = f(from.red);
        to.green = f(from.green);
        to.blue = f(from.blue);
    };
}

/** Apply a one-argument function to each component in a Color. */
template <typename Color, typename Function>
void applyToComponents(Color& color, Function f) {
    componentApplier(f)(color);
}

template <typename Color, typename Function>
void combineComponents(Color& to, Color const& c1, Color const& c2, Function f) {
    componentCombiner(f)(to, c1, c2);
}

template <typename Color, typename Float>
void interpolate(Color& to, Color const& begin, Color const& end, Float r) {
    interpolator<Color>(r)(to, begin, end);
}

}  // namespace fcolor
