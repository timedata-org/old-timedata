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
struct ColorTraits {
    static Color toColor(unsigned int hex) {
        static const auto BYTE = 256;
        auto b = hex % BYTE;
        hex /= BYTE;

        auto g = hex % BYTE;
        hex /= BYTE;

        auto r = hex % BYTE;
        return {{r / 255.0f, g / 255.0f, b / 255.0f}};
    };

    static bool isNearHex(float decimal) {
        return isNearFraction(decimal, 255);
    }

    static bool isGray(Color color) {
        return colorfulness(color) < 0.0001;
    }

    static float strtof(const char *nptr, char const **endptr) {
        char* ep;
        auto r = ::strtof(nptr, &ep);
        *endptr = ep;
        return r;
    }

    static uint32_t fromHex(Color c) {
        uint32_t total = 0;
        static uint32_t const max = 256;
        for (auto& i : c)
            (total *= max) += std::min(max - 1, uint32_t(256 * std::abs(i)));
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

        if (std::all_of(c.begin(), c.end(), isNearHex)) {
            auto hex = fromHex(c);

            auto i = colorNamesInverse().find(hex);
            if (i != colorNamesInverse().end())
                return addNegatives(i->second);
        }

        if (isGray(c))
            return addNegatives("gray " + tdsp::toString(100 * std::abs(c[0]), 5));

        // base!
        return commaSeparated(c, 7);
    }

    static bool toColorNonNegative(char const* name, Color& result) {
        if (not *name)
            return false;

        auto i = colorNames().find(name);
        if (i != colorNames().end()) {
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

    static Color toColor(char const* name) {
        Color result;
        THROW_IF(not toColor(name, result), "Bad color name", name);
        return result;
    }

    static std::string toString(float r, float g, float b) {
        return toString(Color{{r, g, b}});
    }
};

inline bool toColor(char const* s, Color& c, Base base) {
    return base == Base::normal ?
            ColorTraits<Base::normal>::toColor(s, c) :
            ColorTraits<Base::integer>::toColor(s, c);
}

inline Color toColor(char const* name, Base base) {
    return base == Base::normal ?
            ColorTraits<Base::normal>::toColor(name) :
            ColorTraits<Base::integer>::toColor(name);
}

inline std::string colorToString(Color c, Base base) {
    return base == Base::normal ?
            ColorTraits<Base::normal>::toString(c) :
            ColorTraits<Base::integer>::toString(c);
}

inline std::string colorToString(float r, float g, float b, Base base) {
    return base == Base::normal ?
            ColorTraits<Base::normal>::toString(r, g, b) :
            ColorTraits<Base::integer>::toString(r, g, b);
}

}  // tdsp
