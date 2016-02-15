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

    // See e. g. https://en.wikipedia.org/wiki/Alpha_compositing
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

/** Convert between two different types of color. */
template <typename N1, typename A1, typename N2, typename A2=A1>
Color<N2, A2> convert(Color<N1, A1> const&);

/** Create a new color from components and an alpha channel. */
template <typename Number, typename Alpha>
Color<Number, Alpha> color(Number r = 0, Number g = 0, Number b = 0,
                           Alpha a = level::maximum<Alpha>());

template <typename Number>
Color<Number> color(Number r = 0, Number g = 0, Number b = 0);

/** Return the square of the Cartesian distance between . */
template <typename Number, typename Alpha>
Float<Number> distance2(
    Color<Number, Alpha> const&, Color<Number, Alpha> const&);

/** Return the sum of the squares of the pairwise color deltas rg, gb, br. */
template <typename Number, typename Alpha>
Float<Number> greyness2(Color<Number, Alpha> const&);

/** Return a Color with the same components, but no alpha. */
template <typename Number, typename Alpha>
Color<Number> withoutAlpha(Color<Number, Alpha>);

/** Add an alpha to a Color. */
template <typename Number, typename Alpha>
Color<Number, Alpha> withAlpha(Color<Number>, Alpha);

/** Apply a one-argument operator to each component in a Color. */
template <typename Color, typename Operator>
Color applyToComponents(Operator, Color const&);

/** Apply a two-argument operator to each component in two Colors. */
template <typename Color, typename Operator>
Color applyToComponents(Operator, Color const&, Color const&);

/** Apply a one-argument operator to each component in a Color, and
    the alpha channel, if any. */
template <typename Color, typename Operator>
Color applyToComponentsWithAlpha(Operator, Color const&);

/** Apply a two-argument operator to each component in two Colors, and
    the alpha channel, if any. */
template <typename Color, typename Operator>
Color applyToComponentsWithAlpha(Operator, Color const&, Color const&);

/** Interpolate between two colors. */
template <typename Number, typename Float>
Color<Number> interpolate(Color<Number> const&, Color<Number> const&, Float);

}  // namespace fcolor
