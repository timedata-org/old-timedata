#pragma once

#include <timedata/signal/fade.h>

namespace timedata {

template <typename Iter>
void fillSpread(ColorRGB const& c1, ColorRGB const& c2, Iter begin, Iter end,
                Fade const& fade) {
    THROW_IF(end < begin, "Bad spread");
    auto size = end - begin;
    if (size > 0) {
        *begin++ = fadeTo(0, fade, c1, c2);
        if (size > 1) {
            float d = 1.0f / (size - 1);
            for (float i = 1; begin < end; ++begin, ++i)
                *begin = fadeTo(d * i, fade, c1, c2);
        }
    }
}

/** Appends size + 1 elements to the end of a ColorVector, linearly spreading
    from the last element if any, and ending with the color `end`. */
template <typename Color, typename ColorVector>
inline void spreadAppendG(Color const& end, size_t size, ColorVector& colors) {
    if (not size or colors.empty() or colors.back() == end) {
        colors.insert(colors.end(), size + 1, end);
        return;
    }

    auto d = 1.0f / (size + 1);
    auto begin = colors.back();
    Color delta;
    for (size_t j = 0; j < delta.size(); ++j)
        delta[j] = d * (end[j] - begin[j]);

    Color c;
    for (size_t i = 1; i <= size; ++i) {
        for (size_t j = 0; j < c.size(); ++j)
            c[j] = begin[j] + ValueType<Color>{i * delta[j]};
        colors.push_back(c);
    }
    colors.push_back(end);
}

}  // timedata
