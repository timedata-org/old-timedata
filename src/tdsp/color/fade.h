#pragma once

#include <tdsp/base/math.h>
#include <tdsp/base/enum.h>

namespace tdsp {

enum class FadeType {linear, sqr, sqrt, size};

struct Fade {
    float begin = 0, end = 1;
    uint8_t type = static_cast<uint8_t>(FadeType::linear);
};

inline float apply(Fade const& fade, float fader, float x, float y) {
    THROW_IF_GE(fade.type, enumSize<FadeType>(), "Don't understand type");
    auto xratio = fade.begin + fader * fade.end;
    auto yratio = fade.begin + invert(fader) * fade.end;

    switch (static_cast<FadeType>(fade.type)) {
        default:
            break;
        case FadeType::sqr:
            xratio = xratio * xratio * signum(xratio);
            yratio = yratio * yratio * signum(yratio);
            break;
        case FadeType::sqrt:
            xratio = sqrt(std::abs(xratio)) * signum(xratio);
            yratio = sqrt(std::abs(yratio)) * signum(yratio);
            break;
    }

    return xratio * x + yratio + y;
}

template <typename Coll>
void applySame(Fade const& fade, float fader, Coll const& in1, Coll const& in2,
               Coll& out) {
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = apply(fade, fader, in1[i], in2[i]);
}

template <typename Coll>
void applyExtend(Fade const& fade, float fader,
                 Coll const& in1, Coll const& in2, Coll& out) {
    // This is wrong - I shouldn't be changing the size.
    auto size = std::max(in1.size(), in2.size());
    out.resize(size);
    decltype(in1[0]) zero = {{0}};
    auto get = [&] (Coll const& c, size_t i) {
        return i < c.size() ? c[i] : zero;
    };

    for (size_t i = 0; i < size; ++i)
        applySame(fade, fader, get(in1, i), get(in2, i), out[i]);
}

} // tdsp
