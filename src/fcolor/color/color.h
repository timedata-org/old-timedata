#pragma once

#include <limits>
#include <fcolor/base/level.h>

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

/** Clears just the alpha channel, if any, setting it to maximum.
    If the color has no alpha channel then there is no effect. */
template <typename Number, typename Alpha>
void clearAlpha(Color<Number>&);

/** Clears a color's components, setting them to zero, and its alpha channel,
    if any. */
template <typename Color>
void clear(Color&);

/** Create a new color from components and an alpha channel. */
template <typename Number, typename Alpha>
Color<Number, Alpha> color(Number r = 0, Number g = 0, Number b = 0,
                           Alpha a = level::maximum<Alpha>());

template <typename Number>
Color<Number> color(Number r = 0, Number g = 0, Number b = 0);

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
