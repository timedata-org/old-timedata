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
namespace detail {

template <Base base>
struct ColorTraits {
    static constexpr float denormalize(float x) {
        return (base == Base::normal) ? x / 255.0 : x;
    }
    static constexpr float normalize(float x) {
        return (base == Base::integer) ? x * 255.0 : x;
    }

    static Color toColor(unsigned int hex) {
        static const auto BYTE = 256;
        auto b = hex % BYTE;

        hex /= BYTE;
        auto g = hex % BYTE;

        hex /= BYTE;
        auto r = hex % BYTE;

        return {{denormalize(r), denormalize(g), denormalize(b)}};
    };

    static bool isNearHex(float decimal) {
        auto denominator = (base == Base::normal) ? 255 : 1;
        return isNearFraction(decimal, denominator);
    }

    static bool isGray(Color color) {
        return denormalize(colorfulness(color)) < 0.0001;
    }

    static float strtof(const char *nptr, char const **endptr) {
        char* ep;
        auto r = ::strtof(nptr, &ep);
        *endptr = ep;
        return r;
    }

    static uint32_t toHex(Color c) {
        uint32_t total = 0;
        static uint32_t const max = 256;
        for (auto i : c) {
            total *= max;
            i = std::abs(i);
            if (base == Base::normal)
                i *= max;
            total += std::min(max - 1, static_cast<uint32_t>(i));
        }
        return total;
    }

    static std::string toString(Color c) {
        auto addNegatives = [&](std::string const& value) {
            auto s = value;
            auto negative = Sample<RGB, bool>{{c[0] < 0, c[1] < 0, c[2] < 0}};
            if (negative[0] or negative[1] or negative[2]) {
                for (auto n : negative)
                    s += "+-"[n];
            }
            return s;
        };

        auto max = normalize(1.0);
        auto isMax = [=](float x) { return x <= max; };
        if (std::all_of(c.begin(), c.end(), isMax)) {
            if (std::all_of(c.begin(), c.end(), isNearHex)) {
                auto hex = toHex(c);

                auto i = colorMapInverse().find(hex);
                if (i != colorMapInverse().end())
                    return addNegatives(i->second);
            }

            if (isGray(c)) {
                auto gray = 100.0f * normalize(std::abs(c[0]));
                return addNegatives("gray " + tdsp::toString(gray, 5));
            }
        }

        return commaSeparated(c, 7);
    }

    static Color colorFromCommaSeparated(char const* p) {
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

    static bool toColorNonNegative(char const* name, Color& result) {
        if (not *name)
            return false;

        auto i = colorMap().find(name);
        if (i != colorMap().end()) {
            result = toColor(i->second);
            return true;
        }

        static const auto hexPrefixes = {"0x", "0X", "#"};
        for (auto& prefix : hexPrefixes) {
            if (strstr(name, prefix) == name) {
                result = toColor(tdsp::fromHex(name + strlen(prefix)));
                return true;
            }
        }

        char* endptr;

        // Special case for grey and gray.
        if (not (strstr(name, "gray ") and strstr(name, "grey "))) {
            auto gray = static_cast<float>(strtod(name + 5, &endptr)) / 100;
            if (not *endptr) {
                gray = normalize(gray);
                result = {{gray, gray, gray}};
                return true;
            }
            return false;
        }

        try {
            result = colorFromCommaSeparated(name);
            return true;
        } catch (...) {
            return false;
        }
    }

    static bool toColor(char const* name, Color& result) {
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

    static Color toColor(char const* name) {
        Color result;
        THROW_IF(not toColor(name, result), "Bad color name", name);
        return result;
    }
};

} // detail

inline bool stringToColor(char const* s, Color& c, Base base) {
    using namespace tdsp::detail;
    return base == Base::normal ?
            ColorTraits<Base::normal>::toColor(s, c) :
            ColorTraits<Base::integer>::toColor(s, c);
}

inline Color stringToColor(char const* name, Base base) {
    using namespace tdsp::detail;
    return base == Base::normal ?
            ColorTraits<Base::normal>::toColor(name) :
            ColorTraits<Base::integer>::toColor(name);
}

inline std::string colorToString(Color c, Base base) {
    using namespace tdsp::detail;
    return base == Base::normal ?
            ColorTraits<Base::normal>::toString(c) :
            ColorTraits<Base::integer>::toString(c);
}

inline std::string colorToString(float r, float g, float b, Base base) {
    return colorToString({{r, g, b}}, base);
}

bool stringToColor(char const* name, ColorS& cs, Base base) {
    Color c;
    if (not stringToColor(name, c, base))
        return false;
    cs = c;
    return true;
}

Color colorFromHex(uint32_t hex, Base base) {
    if (base == Base::normal)
        return detail::ColorTraits<Base::normal>::toColor(hex);
    return detail::ColorTraits<Base::integer>::toColor(hex);
}

uint32_t hexFromColor(Color const& c, Base base) {
    if (base == Base::normal)
        return detail::ColorTraits<Base::normal>::toHex(c);
    return detail::ColorTraits<Base::integer>::toHex(c);
}

}  // tdsp
