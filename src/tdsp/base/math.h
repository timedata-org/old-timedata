#pragma once

#include <ctype.h>
#include <cmath>
#include <iomanip>
#include <strstream>
#include <type_traits>

#include <tdsp/base/throw.h>

namespace tdsp {

template <typename Number>
Number abs(Number);

template <typename Number>
Number absoluteDifference(Number, Number);

template <typename Number>
bool near(Number, Number, Number diff);

template <typename Number>
bool near(Number, Number);

/** Shift off a single from the right and return it. */
template <typename Number>
bool shift(Number&);


/** Truncate to the nearest integer.  Differs from std::trunc because it always
    returns the same type as it's passed. */
template <typename Number>
Number trunc(Number);

template <typename Collection>
uint64_t fromHex(Collection const&);

uint64_t fromHex(char const*);

// TODO: move elsewhere.
template <typename Collection>
std::string commaSeparated(Collection const&, int decimals = 0);

const auto SIGNED_DIGITS = 19U;  // 9223372036854775807
const auto UNSIGNED_DIGITS = SIGNED_DIGITS + 1;  // 18446744073709551614L

using PowArray = std::array<uint64_t, UNSIGNED_DIGITS>;

PowArray const& powArray();

uint64_t pow10(uint);
uint log10(uint64_t);

void removeTrailing(std::string&, char ch);

/** Convert a float to a string.  Perhaps misguided. */
std::string toString(float, unsigned int decimals = 0);

template <typename T>
void skipSpaces(T* p);

bool isNearFraction(float decimal, unsigned int denominator);

bool cmpToRichcmp(float cmp, int richcmp);

}  // namespace tdsp
