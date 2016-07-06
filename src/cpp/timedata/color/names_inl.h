#pragma once

#include <stdlib.h>
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <map>

#include <timedata/color/names.h>
#include <timedata/base/enum.h>
#include <timedata/base/throw.h>
#include <timedata/base/math_inl.h>
#include <timedata/color/toString.h>
#include <timedata/color/names_table_inl.h>

namespace timedata {
namespace detail {

using HexColor = std::array<uint8_t, 3>;

HexColor hexColor(uint hex) {
    static const auto BYTE = 256;

    auto b = static_cast<uint8_t>(hex % BYTE);
    hex /= BYTE;

    auto g = static_cast<uint8_t>(hex % BYTE);
    hex /= BYTE;

    auto r = static_cast<uint8_t>(hex % BYTE);
    return {{r, g, b}};
};

template <typename Color>
void hexToColor(uint hex, Color& result) {
    auto h = hexColor(hex);
    result = {
        *Color::value_type::scale(h[0]) / 255,
        *Color::value_type::scale(h[1]) / 255,
        *Color::value_type::scale(h[2]) / 255};
};

inline float strtof(const char *nptr, char const **endptr) {
    char* ep;
    auto r = ::strtof(nptr, &ep);
    *endptr = ep;
    return r;
}

inline bool getHexFromName(char const* name, uint& hex) {
    auto i = colorMap().find(name);
    if (i != colorMap().end())
        hex = i->second;
    else if (not fromHexWithPrefix(name, hex))
        return false;
    return true;
}

template <typename Color>
bool colorFromCommaSeparated(char const* p, Color& color) {
    auto getNumber = [&]() {
        auto x = strtof(p, &p);
        skipSpaces(p);
        return static_cast<float>(x);
    };

    color[0] = getNumber();
    if (*p++ != ',')
        return false;

    color[1] = getNumber();
    if (*p++ != ',')
        return false;

    color[2] = getNumber();
    return not *p;
}

template <typename Color>
bool colorFromHex(char const* name, Color& color) {
    uint hex;
    if (not getHexFromName(name, hex))
        return false;

    hexToColor(hex, color);
    return true;
}

template <typename Color>
bool colorFromGray(char const* name, Color& result) {
    // Special case for grey and gray.
    if (not (strstr(name, "gray ") or strstr(name, "grey ")))
        return false;

    char* endptr;
    auto gray = Color::value_type::scale(strtod(name + 5, &endptr) / 100);
    if (*endptr)
        return false;
    result = {gray, gray, gray};
    return true;
}

template <typename Color>
bool toColorNonNegative(char const* name, Color& result) {
    return colorFromHex(name, result) or
        colorFromGray(name, result) or
        colorFromCommaSeparated(name, result);
}

} // detail

template <typename Color>
bool toColor(char const* name, Color& result) {
    // HACK: replace _ with spaces.  Fix once we're done.
    std::string nameS = name;
    for (auto& c: nameS)
        if (c == '_')
            c = ' ';
    name = nameS.c_str();

    auto isSign = [](char ch) { return ch == '-' or ch == '+'; };
    auto len = strlen(name), end = len;
    for (; end > 0 && isSign(name[end - 1]); --end);

    if (end == len)
        return detail::toColorNonNegative(name, result);

    if ((not end) or len - end != 3)
        return false;

    std::string n(name, len - 3);
    if (not detail::toColorNonNegative(n.c_str(), result))
        return false;

    for (auto i = 0; i < 3; ++i) {
        if (name[len - 3 + i] == '-')
            result[i] = - result[i];
    }
    return true;
}

}  // timedata
