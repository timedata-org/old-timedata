#pragma once

#include <cmath>
#include <type_traits>

namespace fcolor {

template <typename Number,
          typename std::enable_if_t<std::is_unsigned<Number>::value, int> = 0>
Number abs(Number x) {
    return x;
}

template <typename Number,
          typename std::enable_if_t<std::is_signed<Number>::value, int> = 0>
Number abs(Number x) {
    return x >= 0 ? x : -x;
}

template <typename X, typename Y>
using common_type = typename std::common_type<X, Y>::type;

template <typename X, typename Y = X>
using is_unsigned = std::is_unsigned<common_type<X, Y>>;

template <typename X, typename Y = X>
using is_signed = std::is_signed<common_type<X, Y>>;

template <typename X,
          typename Y,
          typename std::enable_if_t<is_unsigned<X, Y>::value, int> = 0>
common_type<X, Y> mod(X dividend, Y divisor) {
    return dividend % divisor;
}

template <typename X,
          typename Y,
          typename std::enable_if_t<is_signed<X, Y>::value, int> = 0>
common_type<X, Y> mod(X dividend, Y divisor) {
    return dividend % divisor;
}

template <typename Number>
Number absoluteDifference(Number x, Number y) {
    return (x > y) ? (x - y) : (y - x);
}

template <typename Number>
bool near(Number x, Number y, Number diff) {
    return absoluteDifference(x, y) <= diff;
}

template <typename Number>
bool near(Number x, Number y) {
    return near(x, y, Number(0.000001));
}

template <typename Number>
bool shift(Number& number) {
    auto result = bool(number & 1);
    number /= 2;
    return result;
}

template <typename Number>
Number trunc(Number);

template <typename T,
          typename std::enable_if_t<std::is_integral<T>::value, int> = 0>
T trunc(T x) {
    return x;
}

template <typename T,
          typename std::enable_if_t<std::is_floating_point<T>::value, int> = 0>
T trunc(T x) {
    return std::trunc(x);
}

}  // namespace fcolor
