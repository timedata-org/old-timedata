#pragma once

#include <timedata/color/colorfulness.h>
#include <timedata/color/names_table_inl.h>

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


template <typename Color>
std::string colorToString(Color c) {
    using Range = typename Color::range_type;
    auto bounded = [](ValueType<Color> x) {
        return ValueType<Color>(std::abs(x)).inBand();
    };
    if (std::all_of(c.begin(), c.end(), bounded)) {
        if (std::all_of(c.begin(), c.end(), isNearHex<Range>)) {
            auto hex = colorToHex(c);

            auto i = colorMapInverse().find(hex);
            if (i != colorMapInverse().end())
                return i->second + addNegatives(c);
        }

        if (isGray(c)) {
            auto gray = 100.0f * std::abs(c[0].unscale());
            return "gray " + timedata::toString(gray, 4) + addNegatives(c);
        }
    }
    return commaSeparated(c, 7);
}

}  // timedata
