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

    using number_t = Number;
    using alpha_t = void;

    static const auto hasAlpha = false;
};

template <typename Number, typename Alpha>
struct Color {
    Number red;
    Number green;
    Number blue;

    // See e. g. https://en.wikipedia.org/wiki/Alpha_compositing
    Alpha alpha;

    using number_t = Number;
    using alpha_t = Alpha;
    static const auto hasAlpha = true;
};

// Useful color types.

/** 8-bit color. */
using Color8 = Color<uint8_t>;

/** 8-bit color with alpha. */
using ColorA8 = Color<uint8_t, uint8_t>;

/** 16-bit color. */
using Color16 = Color<uint16_t>;

/** 16-bit color with alpha. */
using ColorA16 = Color<uint16_t, uint16_t>;

/** Floating point color. */
using ColorF = Color<float>;

/** Floating point color with alpha. */
using ColorAF = Color<float, float>;

/** Return a cleared item. */
template <typename T>
T clear();

/** Clears a color's components, setting them to zero, and its alpha channel,
    if any. */
template <typename Color>
void clear(Color&);

// Pack some integer colors into integer words.
uint32_t pack(Color8);
uint32_t pack(ColorA8);
uint64_t pack(Color16);
uint64_t pack(ColorA16);

// Unpack some integer colors from integer words.
Color8 unpack(uint32_t);
ColorA8 unpackAlpha(uint32_t);
Color16 unpack(uint64_t);
ColorA16 unpackAlpha(uint64_t);

/** Convert between two different types of color. */
template <typename N1, typename A1, typename N2, typename A2=A1>
Color<N2, A2> convert(Color<N1, A1> const&);

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
