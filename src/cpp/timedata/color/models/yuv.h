#pragma once

#include <timedata/color/models/rgb.h>
#include <timedata/signal/convert.h>

namespace timedata {

enum class YUV { luma, uchrominance, vchrominance, last = vchrominance };

using ColorYUV = Sample<YUV>;

template <> inline std::string className<ColorYUV>() { return "ColorYUV"; }

namespace converter {

// See: https://en.wikipedia.org/wiki/YUV

template <>
inline void convertSample(ColorRGB const& in, ColorYUV& out) {
    auto r = *in[RGB::red];
    auto g = *in[RGB::green];
    auto b = *in[RGB::blue];
    out[YUV::luma]         =  0.299f   * r +  0.587f   * g +   0.114f   * b;
    out[YUV::uchrominance] = -0.14713f * r + -0.28886f * g +   0.436f   * b;
    out[YUV::vchrominance] =  0.615f   * r + -0.51499f * g +  -0.10001f * g;
}

template <>
inline void convertSample(ColorYUV const& in, ColorRGB& out) {
    auto y = *in[YUV::luma];
    auto i = *in[YUV::uchrominance];
    auto q = *in[YUV::vchrominance];
    out[RGB::red]   = y +                  1.13983f * q;
    out[RGB::green] = y + -0.39465f * i + -0.58060f * q;
    out[RGB::blue]  = y +  2.03211f * i;
}

} // converter
} // timedata
