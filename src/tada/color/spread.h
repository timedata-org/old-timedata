#pragma once

#include <tada/color/colorList.h>
#include <tada/signal/fade.h>

namespace tada {

template <typename Iter>
void fillSpread(Color const& c1, Color const& c2, Iter begin, Iter end,
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

inline
ColorVector fillSpread(Color const& c1, Color const& c2, size_t size,
                       Fade const& fade = {}) {
    ColorVector cl;
    cl.resize(size);
    fillSpread(c1, c2, cl.begin(), cl.end(), fade);
    return cl;
}

/** Appends size + 1 elements to the end of a ColorVector, linearly spreading
    from the last element if any, and ending with the color `end`. */
inline void spreadAppend(ColorVector& colors, size_t size, Color const& end) {
    if (not size or colors.empty() or colors.back() == end) {
        colors.insert(colors.end(), size + 1, end);
        return;
    }
    auto begin = colors.back();
    auto r = begin[0],
         g = begin[1],
         b = begin[2],
         d = 1.0f / (size + 1),
         dr = d * (end[0] - r),
         dg = d * (end[1] - g),
         db = d * (end[2] - b);
    for (size_t i = 1; i <= size; ++i)
        colors.push_back({r + i * dr, g + i * dg, b + i * db});

    colors.push_back(end);
}

}  // tada
