#pragma once

#include <stdint.h>
#include <algorithm>
#include <limits>
#include <type_traits>
#include <fcolor/math/level.h>

namespace fcolor {
namespace level {

template <typename Number>
Float<Number> toFloat(Number n) {
    return convert<Float<Number>>(n);
}

template <
    typename Number,
    typename std::enable_if<std::is_floating_point<Number>::value, int> = 0>
Number maximum() {
    return static_cast<Number>(1.0);
}

template <
    typename Number,
    typename std::enable_if<std::is_integral<Number>::value, int> = 0>
Number maximum() {
    return std::numeric_limits<Number>::max();
}

template <typename Number>
Number limit(Number x) {
    return std::max(Number(0), std::min(maximum<Number>(), x));
}

/* Implementations of convert().

   The math is tricky... and probably none of these work well if To is much
   smaller than From.
*/

/** Are T and U the same class, ignoring const and volatile?
    See http://en.cppreference.com/w/cpp/types/remove_cv
*/
template <typename T, typename U>
using SameClass = std::is_same<std::remove_cv<T>, std::remove_cv<U>>;

/** Convert a type to itself. */
template <
    typename To,
    typename From,
    typename std::enable_if<SameClass<To, From>::value, int> = 0
    >
To convert(From from) {
    return from;
}

/* Convert one floating point type to another - no limiting. */
template <
    typename To,
    typename From,
    typename std::enable_if<std::is_floating_point<To>::value, int> = 0,
    typename std::enable_if<std::is_floating_point<From>::value, int> = 0
    >
To convert(From from) {
    return static_cast<To>(from);
}

/* Convert from int to floating point - no limiting. */
template <
    typename To,
    typename From,
    typename std::enable_if<std::is_floating_point<To>::value, int> = 0,
    typename std::enable_if<std::is_integral<From>::value, int> = 0
    >
To convert(From from) {
    return from / static_cast<To>(maximum<From>());
}

/* Convert from floating point to int - we must limit. */
template <
    typename To,
    typename From,
    typename std::enable_if<std::is_integral<To>::value, int> = 0,
    typename std::enable_if<std::is_floating_point<From>::value, int> = 0
    >
To convert(From from) {
    auto max = static_cast<From>(maximum<To>());
    return static_cast<To>(std::max(From(0), std::min(max, from * (max + 1))));

    // You have to make sure to make the static_cast *before* we add the 1,
    // otherwise there will be integer overflow!
}

/* Convert from one int to a different one. */
template <
    typename To,
    typename From,
    typename std::enable_if<std::is_integral<To>::value, int> = 0,
    typename std::enable_if<std::is_integral<From>::value, int> = 0
    >
To convert(From from) {
    if (maximum<To>() > maximum<From>())
        return from * (maximum<To>() / maximum<From>());
    return static_cast<To>(from / (maximum<From>() / maximum<To>()));
}

} // level
} // fcolor
