#pragma once

#include <math.h>
#include <stdint.h>
#include <fcolor/base/float.h>

namespace fcolor {

////////////////////////////////////////////////////////////////////////////////
//
//  Specializations of Traits.

template <> struct Traits<uint8_t> { using Float = float; };
template <> struct Traits<int8_t> { using Float = float; };

template <> struct Traits<uint16_t> { using Float = float; };
template <> struct Traits<int16_t> { using Float = float; };

template <> struct Traits<uint32_t> { using Float = double; };
template <> struct Traits<int32_t> { using Float = double; };

template <> struct Traits<uint64_t> { using Float = long double; };
template <> struct Traits<int64_t> { using Float = long double; };


////////////////////////////////////////////////////////////////////////////////
//
// modf

template <typename Float>
Pair<Float> modf(Float x) {
    float integral,
          fractional = ::modff(x, &integral);
    return {integral, fractional};
}

template <typename Integer,
          std::enable_if<std::is_integral<Integer>::value, int> = 0>
Integer modf(Integer, Integer&) = delete;

template <>
float modf(float x, float& integral) {
    return ::modff(x, &integral);
}

template <>
double modf(double x, double& integral) {
    return ::modf(x, &integral);
}

template <>
long double modf(long double x, long double& integral) {
        return ::modfl(x, &integral);
}

////////////////////////////////////////////////////////////////////////////////
//
// pow

template <typename Integer,
          typename Exponent,
          std::enable_if<std::is_integral<Integer>::value, int> = 0>
Integer pow(Integer, Exponent) = delete;

template <typename Exponent>
float pow(float x, Exponent e) {
    return ::powf(x, e);
}

template <typename Exponent>
double pow(double x, Exponent e) {
    return ::pow(x, e);
}

template <typename Exponent>
long double pow(long double x, Exponent e) {
    return ::powl(x, e);
}

////////////////////////////////////////////////////////////////////////////////
//
// sqrt

template <typename Integer,
          std::enable_if<std::is_integral<Integer>::value, int> = 0>
Integer sqrt(Integer) = delete;

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

} // fcolor
