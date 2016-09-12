#pragma once

#include <cstddef>
#include <timedata/color/models/rgb.h>
#include <timedata/base/math.h>

namespace timedata {

struct Fade {
    enum class Type {linear, sqr, sqrt, last = sqrt};

    float begin = 0, end = 1;
    Type type = Type::linear;

    float operator()(float fader, float x, float y) const {
        auto xratio = begin + invert(fader) * (end - begin);
        auto yratio = begin + fader * (end - begin);

        switch (type) {
            default:
                break;
            case Fade::Type::sqr:
                xratio = xratio * xratio * signum(xratio);
                yratio = yratio * yratio * signum(yratio);
                break;
            case Fade::Type::sqrt:
                xratio = sqrt(std::abs(xratio)) * signum(xratio);
                yratio = sqrt(std::abs(yratio)) * signum(yratio);
                break;
        }

        // TODO: perhaps we should be applying end and begin after this step?
        return xratio * x + yratio * y;
    }
};

inline
ColorRGB fadeTo(float fader, Fade const& fade, ColorRGB const& in1, ColorRGB const& in2) {
    ColorRGB out;
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = fade(fader, in1[i], in2[i]);
    return out;
}

#if 0
void fadeOver(float fader, Fade const& fade,
              ColorVector const& in1, ColorVector const& in2, ColorVector& out) {
    auto size = std::min(in1.size(), in2.size());
    out.resize(size);
    for (size_t i = 0; i < size; ++i)
        out[i] = fadeTo(fader, fade, in1[i], in2[i]);
}
#endif

} // timedata
