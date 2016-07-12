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
    static const float matrix[3][3] = {
        {0.299f,    0.587f,    0.114f},
        {0.14713f, -0.28886f,  0.436f},
        {0.615f,   -0.51499f, -0.10001f}};

    matrixMultiply(matrix, in, out);
}

template <>
inline void convertSample(ColorYUV const& in, ColorRGB& out) {
    static const float matrix[3][3] = {
        {1.0f,  0.0f,      1.13983f},
        {1.0f, -0.39465f, -0.58060f},
        {1.0f,  2.03211f,  0.0f}};

    matrixMultiply(matrix, in, out);
}

} // converter
} // timedata
