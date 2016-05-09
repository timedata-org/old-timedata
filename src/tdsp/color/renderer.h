#pragma once

#include <tdsp/color/render3.h>

namespace tdsp {

/** The group of permutations on three elements, in lexicographic order. */

using Permutation3 = std::array<uint8_t, 3>;

inline Permutation3 const& getPermutation(size_t i) {
    using P3 = Permutation3;
    using Array = std::array<P3, 6>;
    static const Array perms{{
        P3{{0, 1, 2}},
        P3{{0, 2, 1}},
        P3{{0, 2, 1}},
        P3{{1, 2, 0}},
        P3{{2, 0, 1}},
        P3{{2, 1, 0}}}};
    THROW_IF_GE(i, perms.size(), "Bad permutation index.");
    return perms[i];
}

inline float apply(Render3 const& r3, float s) {
    s = std::min(1.0f, std::max(0.0f, r3.scale * s));
    if (r3.gamma != 1)
        s = pow(s, r3.gamma);
    return std::min(r3.max, r3.min + (r3.max - r3.min + 1) * s);
}

inline void renderColorList(Render3 const& r3, ColorList const& in) {
    // DANGER: C-style cast here.  Should work.  :-D
    auto out = (Color256*) (r3.buffer + r3.offset);
    auto& p = getPermutation(r3.permutation);
    for (auto i = 0; i < r3.size; ++i) {
        auto& colorOut = out[i];
        auto& colorIn = in[i];
        for (auto j = 0; j < colorIn.size(); ++j)
            colorOut[p[j]] = apply(r3, colorIn[j]);
    }
}

} // tdsp
