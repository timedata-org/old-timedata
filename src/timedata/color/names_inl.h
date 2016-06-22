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

// TODO: temporary while getting rid of Base.
inline Color makeNormal(Color const& c) {
    return c;
}

inline Color makeNormal(Color255 const& c) {
    return {*c[0], *c[1], *c[2]};
}

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

template <Base>
struct BaseColor {
    // Temporary class while I dismantle this mess.
    class color_t;
};

template <>
struct BaseColor<Base::normal> {
    using color_t = Color;
};

template <>
struct BaseColor<Base::integer> {
    using color_t = Color255;
};

template <Base BASE>
using ColorType = typename BaseColor<BASE>::color_t;

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

template <Base BASE>
Color colorFromHex(uint hex) {
    ColorType<BASE> c;
    hexToColor(hex, c);
    return makeNormal(c);
};

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

template <typename Color>
bool toColor(char const* name, Color& result) {
    auto isSign = [](char ch) { return ch == '-' or ch == '+'; };
    auto len = strlen(name), end = len;
    for (; end > 0 && isSign(name[end - 1]); --end);

    if (end == len)
        return toColorNonNegative(name, result);

    if ((not end) or len - end != 3)
        return false;

    std::string n(name, len - 3);
    if (not toColorNonNegative(n.c_str(), result))
        return false;

    for (auto i = 0; i < 3; ++i) {
        if (name[len - 3 + i] == '-')
            result[i] = - result[i];
    }
    return true;
}

template <Base BASE>
struct ColorTraits {
    static uint32_t toHex(Color c) {
        if (BASE == Base::integer) {
            for (auto& i: c)
                *i /= 255;
        }
        return toHexNormal(c);
    }

    static std::string toString(Color c) {
        ColorType<BASE> c2(*c[0], *c[1], *c[2]);
        return detail::toString(c2);
    }

    static bool toColor(char const* name, Color& result) {
        ColorType<BASE> c;
        if (not detail::toColor(name, c))
            return false;
        result = makeNormal(c);
        return true;
    }

    static Color toColor(char const* name) {
        Color result;
        THROW_IF(not toColor(name, result), "Bad color name", name);
        return result;
    }
};

} // detail

inline bool stringToColor(char const* s, Color& c, Base base) {
    using namespace timedata::detail;
    return base == Base::normal ?
            ColorTraits<Base::normal>::toColor(s, c) :
            ColorTraits<Base::integer>::toColor(s, c);
}

inline bool stringToColor(char const* s, Color& c) {
    return detail::ColorTraits<Base::normal>::toColor(s, c);
}

inline Color stringToColor(char const* name, Base base) {
    using namespace timedata::detail;
    return base == Base::normal ?
            ColorTraits<Base::normal>::toColor(name) :
            ColorTraits<Base::integer>::toColor(name);
}

inline std::string colorToString(Color c, Base base) {
    using namespace timedata::detail;
    return base == Base::normal ?
            ColorTraits<Base::normal>::toString(c) :
            ColorTraits<Base::integer>::toString(c);
}

inline std::string colorToString(Color c) {
    return detail::ColorTraits<Base::normal>::toString(c);
}

inline std::string colorToString(float r, float g, float b, Base base) {
    return colorToString({r, g, b}, base);
}

inline bool stringToColor(char const* name, ColorS& cs, Base base) {
    Color c;
    if (not stringToColor(name, c, base))
        return false;
    cs = c;
    return true;
}

inline Color colorFromHex(uint32_t hex, Base base) {
    if (base == Base::normal)
        return detail::colorFromHex<Base::normal>(hex);
    return detail::colorFromHex<Base::integer>(hex);
}

inline uint32_t hexFromColor(Color const& c, Base base) {
    if (base == Base::normal)
        return detail::ColorTraits<Base::normal>::toHex(c);
    return detail::ColorTraits<Base::integer>::toHex(c);
}

}  // timedata
