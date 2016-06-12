#pragma once

#include <tada/color/color.h>
#include <tada/color/colorList.h>

namespace tada {

struct Render3 {
    enum class Permutation {rgb, rbg, grb, gbr, brg, bgr};

    float min = 0, max = 255, scale = 1, gamma = 1;
    Permutation permutation = Permutation::rgb;
    size_t offset = 0, size = 0;

    float apply(float s) const {
        s = std::min(1.0f, std::max(0.0f, scale * s));
        if (gamma != 1)
            s = pow(s, gamma);
        return std::min(max, min + (max - min + 1) * s);
    }


    template <typename ColorType = Color>
    ColorType apply(Color c) const {
        static std::vector<std::vector<uint8_t>> const perms = {
            {0, 1, 2},
            {0, 2, 1},
            {1, 0, 2},
            {1, 2, 0},
            {2, 0, 1},
            {2, 1, 0}};
        auto& perm = perms[static_cast<int>(permutation)];

        using Type = typename ColorType::value_type;
        auto r = static_cast<Type>(apply(c[perm[0]]));
        auto g = static_cast<Type>(apply(c[perm[1]]));
        auto b = static_cast<Type>(apply(c[perm[2]]));
        return {{r, g, b}};
    }
};

inline void renderColorVector(
    Render3 const& r3, ColorVector const& in, size_t pos, char* s) {
    // DANGER: C-style cast here.  Should work.  :-D
    // COPY_HACK!
    using Color256 = RGBModelEightBit::Array;
    auto out = (Color256*) s;
    for (size_t i = 0; i < r3.size; ++i)
        out[i] = r3.apply<Color256>(in.at(i + pos));
}

} // tada
