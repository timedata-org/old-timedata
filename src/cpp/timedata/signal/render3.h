#pragma once

#include <timedata/color/models/rgb.h>

namespace timedata {

struct Render3 {
    enum class Permutation {rgb, rbg, grb, gbr, brg, bgr};

    uint8_t min = 0, max = 255;
    float scale = 1.0f, gamma = 1.0f;
    Permutation permutation = Permutation::rgb;
    size_t offset = 0, size = 0;

};

#if 0
    float apply(float s) const {
        s = std::min(1.0f, std::max(0.0f, scale * s));
        if (gamma != 1.0f)
            s = pow(s, gamma);
        return std::min(max, min + (max - min + 1) * s);
    }

    template <typename ColorType = ColorRGB>
    ColorType apply(Color c) const {
        static std::vector<std::vector<uint8_t>> const PERMS = {
            {0, 1, 2},
            {0, 2, 1},
            {1, 0, 2},
            {1, 2, 0},
            {2, 0, 1},
            {2, 1, 0}};
        auto& perm = PERMS[static_cast<int>(permutation)];

        ColorType result;
        using Type = ValueType<ValueType<ColorType>>;
        for (size_t i = 0; i < c.size(); ++i)
            result[i] = static_cast<Type>(apply(c[perm[i]]));
        return result;
    }

inline void renderColorVector(
    Render3 const& r3, ColorVector const& in, size_t pos, char* s) {
    // DANGER: C-style cast here.  Should work.  :-D
    // COPY_HACK!
    using Color256 = Sample<RGB, Range256<uint8_t>>;
    auto out = (Color256*) s;
    for (size_t i = 0; i < r3.size; ++i)
        out[i] = r3.apply<Color256>(in.at(i + pos));
}

#endif

} // timedata
