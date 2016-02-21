#pragma once

#include <limits>
#include <fcolor/color/color.h>
#include <fcolor/base/number_inl.h>
#include <fcolor/base/level_inl.h>

namespace fcolor {

template <typename Color> bool operator==(Color const&, Color const&);
template <typename Color> bool operator!=(Color const&, Color const&);
template <typename Color> bool operator<(Color const&, Color const&);
template <typename Color> bool operator<=(Color const&, Color const&);
template <typename Color> bool operator>(Color const&, Color const&);
template <typename Color> bool operator>=(Color const&, Color const&);


/** Returns a negative number x is if less than, 0 if equals, or positive if x
    is greater than y. */
template <typename Color>
int compare(Color const& x, Color const& y);



template <
    typename Color,
    typename std::enable_if<Color::hasAlpha, int> = 0
    >
int compare(Color const& x, Color const& y) {

}


template <typename Color>
bool operator==(Color const& x, Color const& y) {
    return compare(x, y) == 0;
}

template <typename Color>
bool operator!=(Color const& x, Color const& y) {
    return compare(x, y) != 0;
}

template <typename Color>
bool operator<(Color const& x, Color const& y) {
    return compare(x, y) < 0;
}

template <typename Color>
bool operator<=(Color const& x, Color const& y) {
    return compare(x, y) <= 0;
}

template <typename Color>
bool operator>(Color const& x, Color const& y) {
    return compare(x, y) > 0;
}

template <typename Color>
bool operator>=(Color const& x, Color const& y) {
    return compare(x, y) >= 0;
}

template <typename Color>
void clear(Color& c) {
    c.red = c.green = c.blue = 0;
    clearAlpha(c);
}

template <typename Number>
void clearAlpha(Color<Number>&) {}

template <typename Number, typename Alpha>
void clearAlpha(Color<Number>& n) {
    n.alpha = level::maximum<Alpha>();
}

template <typename Number, typename Alpha>
Color<Number, Alpha> color(Number r, Number g, Number b,
                           Alpha a) {
    return {r, g, b, a};
}

template <typename Number>
Color<Number> color(Number r, Number g, Number b) {
    return {r, g, b};
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

uint32_t pack(Color8 c) {
    return c.red * 0x10000 + c.green * 0x100 + c.blue;
}

uint32_t pack(ColorA8 c) {
    return c.alpha * 0x1000000 + c.red * 0x10000 + c.green * 0x100 + c.blue;
}

uint64_t pack(Color16 c) {
    return c.red * 0x100000000ULL + c.green * 0x10000ULL + c.blue;
}

uint64_t pack(ColorA16 c) {
    return c.alpha * 0x1000000000000ULL +
            c.red * 0x100000000ULL + c.green * 0x10000ULL + c.blue;
}

Color8 unpack(uint32_t i) {
    auto b = static_cast<uint8_t>(i % 0x100);
    i /= 0x100;
    auto g = static_cast<uint8_t>(i % 0x100);
    i /= 0x100;
    auto r = static_cast<uint8_t>(i % 0x100);

    return {r, g, b};
}

ColorA8 unpack(uint32_t i) {
    auto b = static_cast<uint8_t>(i % 0x100);
    i /= 0x100;
    auto g = static_cast<uint8_t>(i % 0x100);
    i /= 0x100;
    auto r = static_cast<uint8_t>(i % 0x100);
    i /= 0x100;
    auto a = static_cast<uint8_t>(i % 0x100);

    return {r, g, b};
}

Color16 unpack(uint64_t i) {
}

ColorA16 unpack(uint64_t i) {
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

template <typename Number, typename Alpha, typename Operator>
Color<Number, Alpha> applyToComponentsWithAlpha(
        Operator op, Color<Number, Alpha> const& color) {
    auto c = applyToComponents(op, color);
    c.alpha = op(color.alpha);
    return c;
}

template <typename Number, typename Operator>
Color<Number> applyToComponentsWithAlpha(
        Operator op, Color<Number> const& color) {
    return applyToComponents(op, color);
}

template <typename Number, typename Alpha, typename Operator>
Color<Number, Alpha> applyToComponentsWithAlpha(
        Operator op,
        Color<Number, Alpha> const& x,
        Color<Number, Alpha> const& y) {
    auto c = applyToComponents(op, x, y);
    c.alpha = op(x.alpha, y.alpha);
    return c;
}

template <typename Number, typename Alpha, typename Operator>
Color<Number> applyToComponentsWithAlpha(
        Operator op,
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

}  // namespace fcolor
