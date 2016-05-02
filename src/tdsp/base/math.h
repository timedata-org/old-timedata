#pragma once

#include <ctype.h>
#include <cmath>
#include <iomanip>
#include <strstream>
#include <type_traits>

namespace tdsp {

template <typename Number,
          typename std::enable_if<std::is_unsigned<Number>::value, int> = 0>
Number abs(Number x) {
    return x;
}

template <typename Number,
          typename std::enable_if<std::is_signed<Number>::value, int> = 0>
Number abs(Number x) {
    return x >= 0 ? x : -x;
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
          typename std::enable_if<std::is_integral<T>::value, int> = 0>
T trunc(T x) {
    return x;
}

template <typename T,
          typename std::enable_if<std::is_floating_point<T>::value, int> = 0>
T trunc(T x) {
    return std::trunc(x);
}

template <typename Collection>
uint64_t fromHex(Collection const& collection) {
    uint64_t total = 0;
    for (auto& i : collection)
        (total *= 256) += std::min(255ULL, static_cast<uint64_t>(256 * i));
    return total;
}

uint64_t fromHex(std::string const& s) {
    uint64_t x;
    std::strstream ss;
    ss << std::hex << s;
    ss >> x;
    return x;
}

// TODO: move elsewhere.
template <typename Collection, typename Stream>
Stream& commaSeparated(Stream& ss, Collection const& collection) {
    bool first = true;
    for (auto& c: collection) {
        if (first)
            first = false;
        else
            ss << ", ";
        ss << c;
    }
    return ss;
}

inline std::strstream makeStream(int precision = 7, int width = 0) {
    std::strstream ss;
    ss << std::setprecision(precision);
    if (width)
        ss << std::setw(width);
    return ss;
}

template <typename Pointer>
void skipSpaces(Pointer& p) {
    for (; isspace(*p); ++p);
};

inline bool isNearFraction(float decimal, unsigned int denominator) {
    auto numerator = denominator * decimal;
    return std::abs(std::round(numerator) - numerator) < 0.0001f;
}

}  // namespace tdsp
