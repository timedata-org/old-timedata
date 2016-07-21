#pragma once

#include <timedata/base/join_inl.h>

namespace timedata {

using GammaTable = std::vector<uint8_t>;

GammaTable makeGammaTable(float gamma, uint8_t begin = 0, uint8_t end = 255);
uint8_t getGamma(GammaTable const&);

////////////////////////////////////////////////////////////////////////////////
//
// Implementation details follow.
//
////////////////////////////////////////////////////////////////////////////////

inline GammaTable makeGammaTable(float gamma, uint8_t begin, uint8_t end) {
    GammaTable table;

    float diff = 1.0f, prevG;
    for (size_t i = 0; i <= 256; ++i) {
        auto g = std::pow(float(i) / 256.0f, 1.0f / gamma);
        if (i)
            diff = std::min(diff, g - prevG);
        prevG = g;
    }

    /* Pick a table size to guarantee that each integer gamma appears
       at least four times in the table, which intuitively guarantees "enough"
       coverage (proof needed). */
    auto size = 4 * static_cast<size_t>(1.0f / diff);
    float width = 1.0f + (end - begin);

    table.reserve(size);

    for (size_t i = 0; i < size; ++i) {
        auto ratio = std::pow(float(i) / float(size), gamma),
             gRaw = begin + ratio * width,
             g = std::min(float(end), gRaw);
        table.push_back(static_cast<uint8_t>(g));
    }

    return table;
}

inline uint8_t getGamma(GammaTable const& table, float x) {
    auto size = static_cast<size_t>(table.size() * std::max(x, 0.0f));
    return table[std::min(size, table.size() - 1)];
}

}  // namespace timedata
