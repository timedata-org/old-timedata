#pragma once

#include <tdsp/signal/render3.h>

namespace tdsp {

/** The group of permutations on three elements, in lexicographic order. */

using Permutation3 = std::array<uint8_t, 3>;

inline Permutation3 const& getPermutation(size_t i) {
    using P3 = Permutation3;
    using Array = std::array<P3, 6>;
    static const Array perms{{
        P3{{0, 1, 2}},
        P3{{0, 2, 1}},
        P3{{1, 0, 2}},
        P3{{1, 2, 0}},
        P3{{2, 0, 1}},
        P3{{2, 1, 0}}}};
    THROW_IF_GE(i, perms.size(), "Bad permutation index.");
    return perms[i];
}

inline void renderColorList(Render3 const& r3, ColorList const& in, char* s) {
    // DANGER: C-style cast here.  Should work.  :-D
    auto out = (Color256*) (s + r3.offset);
    auto& p = getPermutation(r3.permutation);
    for (auto i = 0; i < r3.size; ++i) {
        auto& colorOut = out[i];
        auto& colorIn = in[i];
        for (auto j = 0; j < colorIn.size(); ++j)
            colorOut[p[j]] = r3(colorIn[j]);
    }
}

} // tdsp
