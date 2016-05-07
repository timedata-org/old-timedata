#pragma once

#include <tdsp/color/color.h>

namespace tdsp {

/** The group of permutations on three elements, in lexicographic order. */

using Perm3 = std::array<uint8_t, 3>;

Perm3 const& getPerm(size_t i) {
    using Array = std::array<Perm3, 6>;
    static const Array perms{{
        Perm3{{0, 1, 2}},
        Perm3{{0, 2, 1}},
        Perm3{{0, 2, 1}},
        Perm3{{1, 2, 0}},
        Perm3{{2, 0, 1}},
        Perm3{{2, 1, 0}}}};
    THROW_IF_GE(i, perms.size(), "Bad permutation index.");
    return perms[i];
}

struct Render3 {
    float min, max, brightness, gamma;
    uint8_t perm;

    template <typename T1, typename T2>
    void apply(T1 const& t1, T2& t2, size_t size) const {
        for (size_t i = 0; i < size; ++i)
           apply(t1[i], t2[i]);
    }

    float apply(float s) const {
        s = std::min(1.0f, std::max(0.0f, brightness * s));
        if (gamma != 1)
            s = pow(s, gamma);
        return std::min(max, min + (max - min + 1) * s);
    }

    template <typename In, typename Out>
    void apply(In const& in, Out& out) const {
        auto& p = getPerm(perm);
        using Value = decltype(out[0]);
        for (auto i = 0; i < out.size(); ++i)
            out[p[i]] = static_cast<Value>(apply(in[i]));
    }
};

#if 0
template <typename Strips>
void renderColor(Strips strips, Render render) {

}
#endif

} // tdsp
