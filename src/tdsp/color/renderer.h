#pragma once

#include <tdsp/color/color.h>

namespace tdsp {

/** The group of permutations on three elements, in lexicographic order. */

using Permutation3 = std::array<uint8_t, 3>;

Permutation3 const& getPermutation(size_t i) {
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

struct Render3 {
    float min, max, scale, gamma;
    uint8_t permutation;
    char* buffer;
    size_t offset, size;

    float apply(float s) const {
        s = std::min(1.0f, std::max(0.0f, scale * s));
        if (gamma != 1)
            s = pow(s, gamma);
        return std::min(max, min + (max - min + 1) * s);
    }

    void render(ColorList const& in) {
        // DANGER: C-style cast here.  Should work.  :-D
        auto out = (Color256*) (buffer + offset);
        auto& p = getPermutation(permutation);
        for (auto i = 0; i < size; ++i) {
            auto& colorOut = out[i];
            auto& colorIn = in[i];
            for (auto j = 0; j < colorIn.size(); ++j)
                colorOut[p[j]] = apply(colorIn[j]);
        }
    }
};

} // tdsp
