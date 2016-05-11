#pragma once

#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

#include <tdsp/color/names.h>
#include <tdsp/base/enum.h>
#include <tdsp/base/throw.h>
#include <tdsp/base/math_inl.h>
#include <tdsp/color/colorfulness.h>
#include <tdsp/color/names_table_inl.h>

namespace tdsp {

template <Base base>
Color toColor(unsigned int hex) {
    static const auto BYTE = 256;
    auto b = hex % BYTE;
    hex /= BYTE;

    auto g = hex % BYTE;
    hex /= BYTE;

    auto r = hex % BYTE;
    return {{r / 255.0f, g / 255.0f, b / 255.0f}};
};

inline bool isNearHex(float decimal) {
    return isNearFraction(decimal, 255);
}

inline bool isGray(Color color) {
    return colorfulness(color) < 0.0001;
}

inline float strtof(const char *nptr, char const **endptr) {
    char* ep;
    auto r = ::strtof(nptr, &ep);
    *endptr = ep;
    return r;
}

template <Base base>
uint32_t fromHex(Color c) {
    uint32_t total = 0;
    static uint32_t const max = 256;
    for (auto& i : c)
        (total *= max) += std::min(max - 1, uint32_t(256 * std::abs(i)));
    return total;
}


template <Base base>
std::string toString(Color c) {
    auto addNegatives = [&](std::string const& value) {
        auto s = value;
        auto negative = Sample<RGB, bool>{{c[0] < 0, c[1] < 0, c[2] < 0}};
        if (negative[0] or negative[1] or negative[2]) {
            for (auto n : negative)
                s += "+-"[n];
        }
        return s;
    };

    if (std::all_of(c.begin(), c.end(), isNearHex)) {
        auto hex = fromHex<base>(c);

        auto i = colorNamesInverse().find(hex);
        if (i != colorNamesInverse().end())
            return addNegatives(i->second);
    }

    if (isGray(c))
        return addNegatives("gray " + toString(100 * std::abs(c[0]), 5));

    // base!
    return commaSeparated(c, 7);
}

template <Base base>
bool toColorNonNegative(char const* name, Color& result) {
    if (not *name)
        return false;

    auto i = colorNames().find(name);
    if (i != colorNames().end()) {
        result = toColor<base>(i->second);
        return true;
    }

    static const auto hexPrefixes = {"0x", "0X", "#"};
    for (auto& prefix : hexPrefixes) {
        if (strstr(name, prefix) == name) {
            result = toColor<base>(fromHex(name + strlen(prefix)));
            return true;
        }
    }

    char* endptr;

    // Special case for grey and gray.
    if (not (strstr(name, "gray ") and strstr(name, "grey "))) {
        auto gray = static_cast<float>(strtod(name + 5, &endptr)) / 100;
        if (not *endptr) {
            result = {{gray, gray, gray}};
            return true;
        }
        return false;
    }

    auto getNumber = [&]() {
        auto x = strtod(name, &endptr);
        name = endptr;

        skipSpaces(name);
        return static_cast<float>(x);
    };

    result[0] = getNumber(); // RGB::red
    if (*name++ != ',')
        return false;
    skipSpaces(name);

    result[1] = getNumber();
    if (*name++ != ',')
        return false;
    skipSpaces(name);

    result[2] = getNumber();
    if (*name)
        return false;
    return true;
}

template <Base base>
bool toColor(char const* name, Color& result) {
    auto isSign = [](char ch) { return ch == '-' or ch == '+'; };
    auto len = strlen(name), end = len;
    for (; end > 0 && isSign(name[end - 1]); --end);

    if (end == len)
        return toColorNonNegative<base>(name, result);

    if ((not end) or len - end != 3)
        return false;

    std::string n(name, len - 3);
    if (not toColorNonNegative<base>(n.c_str(), result))
        return false;

    for (auto i = 0; i < 3; ++i) {
        if (name[len - 3 + i] == '-')
            result[i] = - result[i];
    }
    return true;
}

template <Base base>
Color colorFromCommaSeparated(char const* p) {
    auto originalP = p;
    auto getNumber = [&]() {
        auto x = strtof(p, &p);
        skipSpaces(p);
        return static_cast<float>(x);
    };

    auto skipComma = [&]() {
        THROW_IF_NE(*p++, ',', "Expected a comma", originalP);
        skipSpaces(p);
    };

    auto r = getNumber();
    skipComma();

    auto g = getNumber();
    skipComma();

    auto b = getNumber();
    THROW_IF(*p, "Extra characters after end", originalP);

    return {{r, g, b}};
}

template <Base base>
Color toColor(char const* name) {
    Color result;
    THROW_IF(not toColor<base>(name, result), "Bad color name", name);
    return result;
}

template <Base base>
std::string colorToString(float r, float g, float b) {
    return toString<base>(Color{{r, g, b}});
}

inline bool toColor(char const* s, Color& c, Base base) {
    return base == Base::normal ? toColor<Base::normal>(s, c) :
            toColor<Base::integer>(s, c);
}

inline std::string colorToString(float r, float g, float b, Base base) {
    return base == Base::normal ? colorToString<Base::normal>(r, g, b) :
            colorToString<Base::integer>(r, g, b);
}

}  // tdsp
