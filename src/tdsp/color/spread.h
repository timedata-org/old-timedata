#pragma once

#include <tdsp/color/colorList.h>
#include <tdsp/signal/fade.h>

namespace tdsp {

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

}  // tdsp
