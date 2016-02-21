#include <type_traits>
#include <fcolor/color/compare.h>

#pragma once

namespace fcolor {

template <
    typename Number,
    typename std::enable_if<std::is_arithmetic<Number>::value, int> = 0
    >
int compare(Number x, Number y) {
    return (x < y) ? -1 : (x < y) ? 1 : 0;
}

template <typename Number>
int compare(Color<Number> const& x, Color<Number> const& y) {
    if (auto c = compare(x.red, y.red))
        return c;
    if (auto c = compare(x.green, y.green))
        return c;
    if (auto c = compare(x.blue, y.blue))
        return c;
    return 0;
}

template <typename Number, typename Alpha>
int compare(Color<Number, Alpha> const& x, Color<Number, Alpha> const& y) {
    if (auto c = compare(x.red, y.red))
        return c;
    if (auto c = compare(x.green, y.green))
        return c;
    if (auto c = compare(x.blue, y.blue))
        return c;
    if (auto c = compare(x.alpha, y.alpha))
        return c;
    return 0;
}

template <typename T>
bool operator==(T const& x, T const& y) {
    return compare(x, y) == 0;
}

template <typename T>
bool operator!=(T const& x, T const& y) {
    return compare(x, y) != 0;
}

template <typename T>
bool operator<(T const& x, T const& y) {
    return compare(x, y) < 0;
}

template <typename T>
bool operator<=(T const& x, T const& y) {
    return compare(x, y) <= 0;
}

template <typename T>
bool operator>(T const& x, T const& y) {
    return compare(x, y) > 0;
}

template <typename T>
bool operator>=(T const& x, T const& y) {
    return compare(x, y) >= 0;
}

}  // namespace fcolor
