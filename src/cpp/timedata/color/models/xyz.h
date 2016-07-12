#pragma once

#include <timedata/color/models/rgb.h>
#include <timedata/signal/convert.h>

namespace timedata {

enum class XYZ { x, y, z, last = z };

using ColorXYZ = Sample<XYZ>;

template <> inline std::string className<ColorXYZ>() { return "ColorXYZ"; }

namespace converter {

// See: https://en.wikipedia.org/wiki/XYZ

template <>
inline void convertSample(ColorRGB const& in, ColorXYZ& out) {
    static const auto d = 0.17697f;
    static const float matrix[3][3] = {
        {0.49f / d, 0.31f   / d, 0.2f     / d},
        {d     / d, 0.8124f / d, 0.01063f / d},
        {0.0f  / d, 0.01f   / d, 0.99f    / d}};

    matrixMultiply(matrix, in, out);
}

template <>
inline void convertSample(ColorXYZ const& in, ColorRGB& out) {
    static const float matrix[3][3] = {
        { 0.41847f,    0.15866f,  -0.082835f},
        {-0.091169f,   0.25243f,   0.015708f},
        { 0.0009209f, -0.0025498f, 0.1786f}};

    matrixMultiply(matrix, in, out);
}

} // converter
} // timedata
