#pragma once

#include <limits>
#include <fcolor/base/level.h>

namespace fcolor {

template <typename Number, typename Alpha = void>
struct Color;

template <typename Number, typename Alpha, typename Scalar>
Color<Number, Alpha> operator*(Color<Number, Alpha> const&, Scalar);

template <typename Number, typename Alpha, typename Scalar>
Color<Number, Alpha> operator/(Color<Number, Alpha> const&, Scalar);

template <typename Number, typename Alpha, typename Scalar>
Color<Number, Alpha> operator*(Scalar, Color<Number, Alpha> const&);

template <typename Number, typename Alpha = void>
using ColorPair = std::pair<Color<Number, Alpha>, Color<Number, Alpha>>;


template <typename Number>
struct Color<Number, void> {
    Number red;
    Number green;
    Number blue;

    using self_t = Color<Number, void>;
    using number_t = Number;
    using alpha_t = void;

    static const auto hasAlpha = false;

    template <typename T>
    self_t& operator*=(T r) {
        return (*this = (*this * r));
    }

    template <typename T>
    self_t& operator/=(T r) {
        return (*this = (*this / r));
    }
};

template <typename Number, typename Alpha>
struct Color {
    Number red;
    Number green;
    Number blue;

    // See e. g. https://en.wikipedia.org/wiki/Alpha_compositing
    Alpha alpha;

    using self_t = Color<Number, Alpha>;
    using number_t = Number;
    using alpha_t = Alpha;
    static const auto hasAlpha = true;

    template <typename T>
    self_t& operator*=(T r) {
        return (*this = (*this * r));
    }

    template <typename T>
    self_t& operator/=(T r) {
        return (*this = (*this / r));
    }
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

/** Create primary colors. */
template <class Color> Color red();
template <class Color> Color green();
template <class Color> Color blue();

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
template <typename N1, typename A1, typename N2, typename A2>
Color<N1, A1> convert(Color<N2, A2> const&);

/** Return the square of the Cartesian distance between two colors. */
template <typename Number, typename Alpha>
Float<Number> distance2(
    Color<Number, Alpha> const&, Color<Number, Alpha> const&);

/** Return the sum of the squares of the pairwise color deltas rg, gb, br. */
template <typename Number, typename Alpha>
Float<Number> colorfulness2(Color<Number, Alpha> const&);

/** Return a Color with the same components, but no alpha. */
template <typename Number, typename Alpha>
Color<Number> withoutAlpha(Color<Number, Alpha>);

/** Add an alpha to a Color. */
template <typename Number, typename Alpha>
Color<Number, Alpha> withAlpha(Color<Number>, Alpha);

/** Interpolate between two colors. */
template <typename Color, typename Float>
void interpolate(Color& result, Color const& begin, Color const& end, Float);

/** Combine two colors into one by component.*/
template <typename Color, typename Function>
void combineComponents(Color&, Color const&, Color const&, Function);

/** Apply a one-argument function to each component in a Color. */
template <typename Color, typename Function>
void applyToComponents(Color&, Function);

}  // namespace fcolor
