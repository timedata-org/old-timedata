#pragma once

#include <limits>
#include <fcolor/math/level.h>

namespace fcolor {

template <typename Number, typename Alpha = void>
struct Color;

template <typename Number>
struct Color<Number, void> {
    Number red;
    Number green;
    Number blue;
};

template <typename Number, typename Alpha>
struct Color {
    Number red;
    Number green;
    Number blue;

    Alpha alpha;
};

template <typename Number, typename Alpha>
Color<Number, Alpha> color(Number r, Number g, Number b, Alpha a) {
    return {r, g, b, a};
}

template <typename Number>
Color<Number> color(Number r, Number g, Number b) {
    return {r, g, b};
}

template <typename Number, typename Alpha>
Float<Number> distance2(
    Color<Number, Alpha> const&, Color<Number, Alpha> const&);

/** Return the sum of the squares of the color differences. */
template <typename Number, typename Alpha>
Float<Number> greyness2(Color<Number, Alpha> const&);

template <typename Number, typename Alpha>
Color<Number> withoutAlpha(Color<Number, Alpha>);

template <typename Number, typename Alpha>
Color<Number, Alpha> withAlpha(Color<Number>, Alpha);

template <typename Color, typename Operator>
Color applyToComponents(Operator, Color const&);

template <typename Color, typename Operator>
Color applyToComponents(Operator, Color const&, Color const&);

template <typename Number, typename Alpha, typename Float>
Color<Number, Alpha> interpolate(
    Color<Number, Alpha> const&, Color<Number, Alpha> const&, Float ratio);

}  // namespace fcolor
