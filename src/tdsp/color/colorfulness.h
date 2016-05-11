#pragma once

#include <tdsp/color/color.h>

namespace tdsp {

/** How far away is this color from gray, defined as the maximum distance
    between any two pairs of color. */
float colorfulness(Color color);

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Implementation details follow.

template <typename Collection, typename Function>
void forEachPair(Collection const& coll, Function f) {
    for (size_t i = 0; i + 1 < coll.size(); ++i)
        for (size_t j = i + 1; j < coll.size(); ++j)
            f(coll[i], coll[j]);
}

template <typename Collection>
typename Collection::value_type maxPairedDistanceAbs(Collection const& coll) {
    using Number = typename Collection::value_type;
    Number result = 0;
    forEachPair(coll, [&](Number x, Number y) {
        result = std::max(result, std::abs(std::abs(x) - std::abs(y)));
    });
    return result;
}

inline float colorfulness(Color color) {
    return maxPairedDistanceAbs(color);
}

}  // tdsp
