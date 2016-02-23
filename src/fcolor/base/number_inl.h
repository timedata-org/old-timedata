#pragma once

#include <math.h>
#include <stdint.h>
#include <cmath>
#include <memory>
#include <type_traits>
#include <fcolor/base/number.h>

namespace fcolor {

////////////////////////////////////////////////////////////////////////////////
//
//  Specializations of Traits.
//
////////////////////////////////////////////////////////////////////////////////

template <> struct Traits<uint8_t> { using Float = float; };
template <> struct Traits<int8_t> { using Float = float; };

template <> struct Traits<uint16_t> { using Float = float; };
template <> struct Traits<int16_t> { using Float = float; };

template <> struct Traits<uint32_t> { using Float = double; };
template <> struct Traits<int32_t> { using Float = double; };

template <> struct Traits<uint64_t> { using Float = long double; };
template <> struct Traits<int64_t> { using Float = long double; };

template <typename T>
struct Traits<std::shared_ptr<T>> {
    using Float = typename Traits<T>::Float;
};

template <typename Float>
Pair<Float> modf(Float x) {
    Float integral, fractional = std::modf(x, &integral);
    return {integral, fractional};
}

// https://stackoverflow.com/questions/1727881/
template <>
float pi<float>() {
    return 3.141592653f;
}

template <>
double pi<double>() {
    return 3.14159265358979323846;
}

template <>
long double pi<long double>() {
    return 3.141592653589793238462643383279502884L;
}

template <
    typename Number,
    typename std::enable_if<std::is_integral<Number>::value, int> = 0>
Number pi() = delete;

} // fcolor
