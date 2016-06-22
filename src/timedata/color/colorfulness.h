#pragma once

#include <timedata/color/color.h>

namespace timedata {

/** How far away is this color from gray, defined as the maximum distance
    between any two pairs of color. */
template <typename Color>
ValueType<Color> colorfulness(Color const&);

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

template <typename Color>
ValueType<Color> colorfulness(Color const& color) {
    ValueType<Color> result = 0;
    forEachPair(color, [&](ValueType<Color> x, ValueType<Color> y) {
        result = std::max(result, (x - y).abs());
    });
    return result;
}

}  // timedata
