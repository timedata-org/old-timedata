#pragma once

#include <math.h>
#include <stdint.h>
#include <fcolor/math/float.h>

namespace fcolor {

template <typename T>
float pow(float x, T e) {
    return ::powf(x, e);
}

template <typename T>
double pow(double x, T e) {
    return ::pow(x, e);
}

template <typename T>
long double pow(long double x, T e) {
    return ::powl(x, e);
}

template <>
float sqrt(float x) {
    return ::sqrtf(x);
}

template <>
double sqrt(double x) {
    return ::sqrt(x);
}

template <>
long double sqrt(long double x) {
    return ::sqrtl(x);
}

template <typename Integer,
          typename T,
          std::enable_if<std::is_integral<Integer>::value, int> = 0>
Integer pow(Integer, T) = delete;

template <typename Integer,
          std::enable_if<std::is_integral<Integer>::value, int> = 0>
Integer sqrt(Integer) = delete;

/*
  Specializations of Traits.
*/

template <> struct Traits<uint8_t> { using Float = float; };
template <> struct Traits<int8_t> { using Float = float; };

template <> struct Traits<uint16_t> { using Float = float; };
template <> struct Traits<int16_t> { using Float = float; };

template <> struct Traits<uint32_t> { using Float = double; };
template <> struct Traits<int32_t> { using Float = double; };

template <> struct Traits<uint64_t> { using Float = long double; };
template <> struct Traits<int64_t> { using Float = long double; };

} // fcolor
