#pragma once

#include <timedata/color/colorfulness.h>
#include <timedata/color/names_table_inl.h>
#include <timedata/color/models/rgb.h>
#include <timedata/signal/convert_inl.h>

namespace timedata {

template <typename Range>
bool isNearHex(Ranged<Range> number) {
    return isNearFraction(number, 255.0f / Range::RANGE);
}

template <typename Color>
std::string addNegatives(Color const& c) {
    std::string s;
    auto r = (*c[0] < 0), g = (*c[1] < 0), b = (*c[2] < 0);
    if (r or g or b) {
        for (auto i: {r, g, b})
            s += "+-"[i];
    }
    return s;
};

template <typename Color>
bool isGray(Color color) {
    return colorfulness(color).unscale() < 0.0001;
}

template <typename Color>
uint32_t colorToHex(Color c) {
    uint32_t total = 0;
    static uint32_t const MAX = 256;
    for (auto i : c) {
        total *= MAX;
        auto x = MAX * std::abs(i.unscale());
        total += std::min(MAX - 1, static_cast<uint32_t>(x));
    }
    return total;
}

inline std::string colorToStringNormal(ColorRGB const& c) {
    auto bounded = [](Ranged<> x) {
        return Ranged<>(std::abs(x)).inBand();
    };
    if (std::all_of(c.begin(), c.end(), bounded)) {
        if (std::all_of(c.begin(), c.end(), isNearHex<Normal<>>)) {
            auto hex = colorToHex(c);

            auto i = colorMapInverse().find(hex);
            if (i != colorMapInverse().end())
                return i->second + addNegatives(c);
        }

        if (isGray(c)) {
            auto gray = 100.0f * std::abs(c[0]);
            return "gray " + timedata::toString(gray, 4) + addNegatives(c);
        }
    }
    return "";
}

inline std::string colorToString(ColorRGB const& c) {
    auto s = colorToStringNormal(c);
    return s.empty() ? commaSeparated(c, 7) : s;
}

template <typename Color>
std::string colorToString(Color const& c) {
    ColorRGB normal;
    converter::convertSample(c, normal);
    auto s = colorToStringNormal(normal);
    return s.empty() ? commaSeparated(c, 7) : s;
}

}  // timedata
