#pragma once

#include <ctype.h>
#include <cmath>
#include <iomanip>
#include <strstream>
#include <type_traits>

#include <tdsp/base/throw.h>

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

inline uint64_t fromHex(char const* s) {
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

const auto SIGNED_DIGITS = 19U;  // 9223372036854775807
const auto UNSIGNED_DIGITS = SIGNED_DIGITS + 1;  // 18446744073709551614L

inline uint64_t pow10(uint log) {
    THROW_IF_GT(log, UNSIGNED_DIGITS, "Overflow.");
    static uint64_t exp[] = {
        1ULL,
        10ULL,
        100ULL,
        1000ULL,
        10000ULL,
        100000ULL,
        1000000ULL,
        10000000ULL,
        100000000ULL,
        1000000000ULL,
        10000000000ULL,
        100000000000ULL,
        1000000000000ULL,
        10000000000000ULL,
        100000000000000ULL,
        1000000000000000ULL,
        10000000000000000ULL,
        100000000000000000ULL,
        1000000000000000000ULL,
        10000000000000000000ULL
    };
    return exp[log];
}

/** Convert a float to a string */

enum class ToStringStrategy { raw, noTrailingZeroes };

inline std::string toString(
        float x, unsigned int decimals,
        ToStringStrategy strat = ToStringStrategy::noTrailingZeroes) {
    auto number = std::to_string(std::llround(x * pow10(decimals)));
    if (decimals) {
        number.insert(&number[number.size() - decimals], '.');
        if (strat == ToStringStrategy::noTrailingZeroes) {
            while (number.back() == '0')
                number.resize(number.size() - 1);
            if (number.back() == '.')
                number.resize(number.size() - 1);
        }
    }
    return number;
}

inline std::strstream makeStream(int precision = 7, int width = 0) {
    std::strstream ss;
    ss << std::setprecision(precision);
    if (width)
        ss << std::setw(width);
    return std::move(ss);
}

template <typename Pointer>
void skipSpaces(Pointer* p) {
    for (; isspace(*p); ++p);
};

inline bool isNearFraction(float decimal, unsigned int denominator) {
    auto numerator = denominator * decimal;
    return std::abs(std::round(numerator) - numerator) < 0.0001f;
}

inline bool cmpToRichcmp(float cmp, int richcmp) {
    switch (richcmp) {
        case 0: return cmp < 0;
        case 1: return cmp <= 0;
        case 2: return cmp == 0;
        case 3: return cmp != 0;
        case 4: return cmp > 0;
        case 5: return cmp >= 0;
        default:  THROW("Bad richcmp", richcmp); return false;
    }
}

}  // namespace tdsp
