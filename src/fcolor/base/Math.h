#pragma once

// #include <fcolor/Fcolor.h>

namespace fcolor {

template <typename Number>
bool isNegative(Number n) { return n < 0; }

inline bool isNegative(unsigned char) { return false; }
inline bool isNegative(unsigned short) { return false; }
inline bool isNegative(unsigned int) { return false; }
inline bool isNegative(unsigned long) { return false; }
inline bool isNegative(unsigned long long) { return false; }

template <typename Number>
Number abs(Number x) { return isNegative(x) ? -x : x; }

template <typename X, typename Y>
auto mod(X dividend, Y divisor) -> decltype(dividend % divisor) {
    auto modulo = dividend % divisor;
    if (isNegative(modulo))
        modulo += abs(divisor);
    return modulo;
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

/** Generically get the size of an enum whose last element is `size`. */
template <typename Enum,
          typename std::enable_if_t<std::is_enum<Enum>::value, int> = 0>
constexpr size_t enumSize(Enum element = Enum::size) {
    return static_cast<size_t>(element);
}

template <typename Enum,
          typename Functor,
          typename std::enable_if_t<std::is_enum<Enum>::value, int> = 0>
void forEach(Functor f) {
    for (size_t i = 0; i < enumSize<Enum>(); ++i)
        f(static_cast<Enum>(i));
}

}  // namespace fcolor
