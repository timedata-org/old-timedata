#pragma once

#include <cstddef>
#include <timedata/base/join_inl.h>

namespace timedata {

using GammaTable = std::vector<uint8_t>;

GammaTable makeGammaTable(
        float gamma, float offset = 0.0, uint8_t min = 0, uint8_t max = 255);

uint8_t getGamma(GammaTable const&, float x);

////////////////////////////////////////////////////////////////////////////////
//
// Implementation details follow.
//
////////////////////////////////////////////////////////////////////////////////

inline GammaTable makeGammaTable(
        float gamma, float offset, uint8_t min, uint8_t max) {
    auto iGamma = 1.0f / gamma;
    auto diff = 1.0f - std::pow(255.0f / 256.0f, iGamma);

    /* Pick a table size to guarantee that each integer gamma appears
       at least four times in the table, which intuitively guarantees "enough"
       coverage (proof needed). */
    auto size = 4 * static_cast<size_t>(1.0f / diff);
    float width = 1.0f + (max - min);

    GammaTable table;
    table.reserve(size);

    for (size_t i = 0; i < size; ++i) {
        auto ratio = std::pow(float(i) / float(size), gamma),
             gRaw = min + ratio * width + offset,
             g = std::min(float(max), gRaw);
        table.push_back(static_cast<uint8_t>(g));
    }

    return table;
}

inline uint8_t getGamma(GammaTable const& table, float x) {
    auto size = static_cast<size_t>(table.size() * std::max(x, 0.0f));
    return table[std::min(size, table.size() - 1)];
}

}  // namespace timedata
