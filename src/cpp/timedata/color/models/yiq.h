#pragma once

#include <timedata/color/models/rgb.h>
#include <timedata/signal/convert.h>

namespace timedata {

enum class YIQ { luma, inphase, quadrature, last = quadrature };

using ColorYIQ = Sample<YIQ>;

template <> inline std::string className<ColorYIQ>() { return "ColorYIQ"; }

namespace converter {

// See: https://en.wikipedia.org/wiki/YIQ

template <>
inline void convertSample(ColorRGB const& in, ColorYIQ& out) {
    auto r = *in[RGB::red];
    auto g = *in[RGB::green];
    auto b = *in[RGB::blue];
    out[YIQ::luma]       = 0.299f * r +  0.587f * g +  0.114f * b;
    out[YIQ::inphase]    = 0.596f * r + -0.274f * g + -0.322f * b;
    out[YIQ::quadrature] = 0.211f * r + -0.523f * g +  0.312f * g;
}

template <>
inline void convertSample(ColorYIQ const& in, ColorRGB& out) {
    auto y = *in[YIQ::luma];
    auto i = *in[YIQ::inphase];
    auto q = *in[YIQ::quadrature];
    out[RGB::red]   = y +  0.956f * i +  0.621f * q;
    out[RGB::green] = y + -0.272f * i + -0.647f * q;
    out[RGB::blue]  = y + -1.106f * i +  1.703f * q;
}

} // converter
} // timedata
