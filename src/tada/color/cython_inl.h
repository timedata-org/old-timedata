#pragma once

#include <tada/base/enum.h>
#include <tada/base/math.h>
#include <tada/base/rotate.h>
#include <tada/color/color.h>
#include <tada/color/names_inl.h>

namespace tada {
namespace color {

using ColorCpp = Color;

inline std::string colorToString(Color const& x) {
    return colorToString(x, Base::normal);
}

inline bool stringToColor(std::string const& x, Color& c) {
    return stringToColor(x.c_str(), c, Base::normal);
}

inline Color magic_abs(Color const& x) {
    return {{std::abs(x[0]), std::abs(x[1]), std::abs(x[2])}};
}

inline Color magic_ceil(Color const& x) {
    return {{std::ceil(x[0]), std::ceil(x[1]), std::ceil(x[2])}};
}

inline Color magic_floor(Color const& x) {
    return {{std::floor(x[0]), std::floor(x[1]), std::floor(x[2])}};
}

inline Color magic_invert(Color const& x) {
    return {{invert(x[0]), invert(x[1]), invert(x[2])}};
}

inline Color magic_neg(Color const& x) {
    return {{-x[0], -x[1], -x[2]}};
}

inline Color magic_round(Color const& x) {
    // TODO: two argument version!
    return {{std::round(x[0]), std::round(x[1]), std::round(x[2])}};
}

inline Color magic_trunc(Color const& x) {
    return {{std::trunc(x[0]), std::trunc(x[1]), std::trunc(x[2])}};
}

inline int magic_hash(Color const& x) {
    // http://stackoverflow.com/a/2909572/43839
    auto h = ((x[0] * 101) + x[1] * 101) + x[2];
    return static_cast<int>(256 * h);
}

inline Color magic_add(Color const& x, Color const& y) {
    return {{x[0] + y[0], x[1] + y[1], x[2] + y[2]}};
}

inline Color magic_truediv(Color const& x, Color const& y) {
    return {{divPython(x[0], y[0]),
             divPython(x[1], y[1]),
             divPython(x[2], y[2])}};
}

inline Color magic_mod(Color const& x, Color const& y) {
    return {{modPython(x[0], y[0]),
             modPython(x[1], y[1]),
             modPython(x[2], y[2])}};
}

inline Color magic_mul(Color const& x, Color const& y) {
    return {{x[0] * y[0], x[1] * y[1], x[2] * y[2]}};
}

inline Color magic_sub(Color const& x, Color const& y) {
    return {{x[0] - y[0], x[1] - y[1], x[2] - y[2]}};
}

inline Color limit_min(Color const& x, Color const& y) {
    return {{std::max(x[0], y[0]),
             std::max(x[1], y[1]),
             std::max(x[2], y[2])}};
}

inline Color limit_max(Color const& x, Color const& y) {
    return {{std::min(x[0], y[0]),
             std::min(x[1], y[1]),
             std::min(x[2], y[2])}};
}

inline Color rotated(Color const& x, int pos) {
    auto y = x;
    rotate(y, pos);
    return y;
}

inline float distance(Color const& x, Color const& y) {
    return tada::distance(x, y);
}

inline float distance2(Color const& x, Color const& y) {
    return tada::distance2(x, y);
}

inline Color magic_pow(Color const& x, Color const& y) {
    return {{powPython(x[0], y[0]),
             powPython(x[1], y[1]),
             powPython(x[2], y[2])}};
}

inline Color magic_pow(Color const& x, Color const& y, Color const& z) {
    return {{modPython(powPython(x[0], y[0]), z[0]),
             modPython(powPython(x[1], y[1]), z[1]),
             modPython(powPython(x[2], y[2]), z[2])}};
}

inline std::vector<std::string> const& colorNames() {
    return tada::colorNames();
}

inline bool fixKey(int& key, size_t size) {
    if (key < 0)
        key += size;
    return key >= 0 and key < int(size);
}

inline float compare(Color const& x, Color const& y) {
    if (auto a = x[0] - y[0])
        return a;
    if (auto a = x[1] - y[1])
        return a;
    if (auto a = x[2] - y[2])
        return a;
    return 0.0f;
}

inline bool compare(Color const& x, Color const& y, int richCmp) {
    return cmpToRichcmp(compare(x, y), richCmp);
}

inline Color from_hex(uint32_t hex) {
    return colorFromHex(hex, Base::normal);
}

inline uint32_t to_hex(Color const& c) {
    return hexFromColor(c, Base::normal);
}

} // color
} // tada
