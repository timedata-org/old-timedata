#pragma once

#include <ctype.h>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <type_traits>

#include <tada/base/throw.h>

namespace tada {

template <typename Number>
Number abs(Number);

template <typename Number>
Number absoluteDifference(Number, Number);

template <typename Number>
bool near(Number, Number, Number diff);

template <typename Number>
bool near(Number, Number);

/** Shift off a single bit from the right of an integer and return it. */
template <typename Number>
bool shift(Number&);


/** Truncate to the nearest integer.  Differs from std::trunc because it always
    returns the same type as it's passed. */
template <typename Number>
Number trunc(Number);

// TODO: move elsewhere.
template <typename Collection>
std::string commaSeparated(Collection const&, int decimals = 0);

const auto SIGNED_DIGITS = 19U;  // 9223372036854775807
const auto UNSIGNED_DIGITS = SIGNED_DIGITS + 1;  // 18446744073709551614L

using PowArray = std::array<uint64_t, UNSIGNED_DIGITS>;

PowArray const& powArray();

uint64_t pow10(uint);
uint log10(uint64_t);
uint64_t fromHex(char const*);
bool isHex(char const*);

void removeTrailing(std::string&, char ch);

/** Convert a float to a string. */
std::string toString(float, unsigned int decimals = 0);

template <typename T>
void skipSpaces(T* p);

bool isNearFraction(float decimal, unsigned int denominator);

bool cmpToRichcmp(float cmp, int richcmp);

template <typename C1, typename C2>
int compareContainers(C1 const&, C2 const&);

template <typename Struct>
void clearStruct(Struct& s) {
    s = Struct{};
}

inline float invert(float x, float center = 1.0f) {
    return (x >= 0) ? (center - x) : -(x + center);
}

inline float normalize(float x, float max = 1.0f) {
    return std::min(max, std::max(0.0f, x));
}

template <typename T>
T signum(T x) {
    return static_cast<T>(x > 0 ? 1 : x < 0 ? -1 : 0);
}

inline uint8_t to256(float x) {
    return static_cast<uint8_t>(std::min(255.0f, std::max(0.0f, x * 256)));
}

/** A version of / that always returns a value.
    Dividing a positive number by zero returns inf;
    dividing a negative number by zero returns -inf;
    dividing zero by zero returns nan.
*/
float divPython(float x, float y);

/** A version of pow that always returns a value and preserves sign.
    If x > 0, returns pow(x, y).
    If x < 0, returns -pow(-x, y)
    If x == 0 and y == 1, returns 1
    Otherwise, returns 0.
*/
float powPython(float x, float y);

/** A version of mod that always returns a value and uses Python's sign
    convention.
*/
float modPython(float x, float y);

template <typename Collection>
typename Collection::value_type hashPython(Collection const&);

}  // namespace tada
