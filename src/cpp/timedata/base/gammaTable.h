#pragma once

#include <timedata/base/join_inl.h>

namespace timedata {

struct GammaTable {
    float const gamma;
    std::vector<uint8_t> table;

    GammaTable(float);
    uint8_t operator()(float x) const;
};

////////////////////////////////////////////////////////////////////////////////
//
// Implementation details follow.
//
////////////////////////////////////////////////////////////////////////////////

inline GammaTable::GammaTable(float gamma_) : gamma(gamma_) {
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
    table.reserve(size);

    for (size_t i = 0; i < size; ++i) {
        auto g = 256.0f * std::pow(float(i) / float(size), gamma);
        table.push_back(static_cast<uint8_t>(g));
    }
}

inline uint8_t GammaTable::operator()(float x) const {
    if (x <= 0.0f)
        return 0;
    if (x >= 1.0f)
        return 0xFF;
    auto i = static_cast<size_t>(x * table.size());
    return table[i];
}

}  // namespace timedata
