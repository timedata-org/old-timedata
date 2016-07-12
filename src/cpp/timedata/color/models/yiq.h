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
    static const float matrix[3][3] = {
        {0.299f,  0.587f,  0.114f},
        {0.596f, -0.274f, -0.322f},
        {0.211f, -0.523f,  0.312f}};

    matrixMultiply(matrix, in, out);
}

template <>
inline void convertSample(ColorYIQ const& in, ColorRGB& out) {
    static const float matrix[3][3] = {
        {1.0f,  0.956f,  0.621f},
        {1.0f, -0.272f, -0.647f},
        {1.0f, -1.106f,  1.703f}};

    matrixMultiply(matrix, in, out);
}

} // converter
} // timedata
