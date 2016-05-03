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
template <typename Collection>
std::string commaSeparated(Collection const& collection, int decimals) {
    std::string result;

    bool first = true;
    for (auto& c: collection) {
        if (first)
            first = false;
        else
            result += ", ";
        result += toString(c, decimals);
    }
    return result;
}

PowArray const& powArray() {
    static const PowArray array{{
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
    }};
    return array;
};

inline uint64_t pow10(uint log) {
    return powArray()[log];
}

inline uint log10(uint64_t exp) {
    auto& pa = powArray();
    uint b = std::upper_bound(pa.begin(), pa.end(), exp) - pa.begin();
    return std::max(b, uint(1)) - 1;
}

inline void removeTrailing(std::string& s, char ch) {
    auto i = s.size();
    for (; i > 0 and s[i - 1] == ch; --i);
    s.resize(i);
}

/** Convert a float to a string. */
inline std::string toString(float x, unsigned int decimals) {
    size_t size = log10(x) + 3 + decimals;
    std::string number(size, ' ');
    number.resize(snprintf(&number[0], size, "%1.*f", decimals, x));
    if (number.find('.') != std::string::npos) {
        removeTrailing(number, '0');
        removeTrailing(number, '.');
    }
    return number;
}

template <typename T>
void skipSpaces(T* p) {
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
