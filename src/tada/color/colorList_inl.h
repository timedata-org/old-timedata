#pragma once

#include <tada/color/colorList.h>
#include <tada/base/make.h>
#include <tada/base/math_inl.h>
#include <tada/color/hsv_inl.h>
#include <tada/color/names_inl.h>
#include <tada/signal/slice.h>

namespace tada {

inline
ColorVector duplicate(ColorVector const& v, size_t count) {
    ColorVector result;
    for (size_t i = 0; i < count; ++i)
        result.insert(result.end(), v.begin(), v.end());
    return result;
}

inline
void reverse(ColorVector& v) {
    std::reverse(v.begin(), v.end());
}

inline std::string toString(ColorVector const& colors, Base base) {
    std::string result = "(";
    for (auto& c : colors) {
        if (result.size() > 1)
            result += ", ";
        auto s = colorToString(c, base);
        auto digit = isdigit(s[0]) ? 1 : 0;
        result += "'("[digit];
        result += s;
        result += "')"[digit];
    }
    result += ")";
    return result;
}

inline
ColorVector sliceVector(
        ColorVector const& in, int begin, int end, int step) {
    // TODO: is this used?
    auto slice = make<Slice>(begin, end, step);
    ColorVector out;
    forEach(slice, [&](int j) { out.push_back(in[j]); });
    return out;
}

inline
bool sliceIntoVector(ColorVector const& in, ColorVector& out,
                     int begin, int end, int step) {
    auto slice = make<Slice>(begin, end, step);
    auto size = slice.size();

    if (in.size() == size) {
        auto i = in.begin();
        forEach(slice, [&](int j) { out[j] = *(i++); });
        return true;
    }

    if (step != 1)
        return false;

    auto ob = out.begin() + begin;
    if (in.size() < size) {
        // Shrink!  Copy the input, then erase the remains.
        std::copy(in.begin(), in.end(), ob);
        out.erase(ob + in.size(), ob + size);
    } else {
        // Grow!  Copy the first segment, then insert the second.
        std::copy(in.begin(), in.begin() + size, ob);
        out.insert(ob + slice.begin, in.begin() + size, in.end());
    }

    return true;
}

template <typename Function>
void forEachColorComponent(ColorVector& colors, Function f) {
    // TODO: phase this out in favor of the functional version.
    for (auto& color : colors)
        for (auto& c : color)
            f(c);
}

template <typename Function>
void forEachComponent(ColorVector& colors, Function f) {
    for (auto& color : colors)
        for (auto& c : color)
            c = f(c);
}

template <typename Function>
void forEachColorComponent(ColorVector const& in, ColorVector& out, Function f) {
    if (out.size() < in.size())
        out.resize(in.size());

    for (size_t i = 0; i < in.size(); ++i)
        for (size_t j = 0; j < in[i].size(); ++j)
            f(in[i][j], out[i][j]);
}

inline void absInto(ColorVector& out) {
    forEachComponent(out, [](float x) { return std::abs(x); });
}

inline void ceilInto(ColorVector& out) {
    forEachComponent(out, [](float x) { return std::ceil(x); });
}

inline void floorInto(ColorVector& out) {
    forEachComponent(out, [](float x) { return std::floor(x); });
}

inline void invertColor(ColorVector& out) {
    forEachComponent(out, [](float x) { return (x > 0 ? 1.0 : -1.0) - x; });
}

inline void negateColor(ColorVector& out) {
    forEachComponent(out, [](float x) { return -x; });
}

inline float roundN(float x, uint digits) {
    auto p = static_cast<float>(pow10(digits));
    return round(x * p) / p;
}

inline void roundColor(ColorVector& out, uint digits) {
    forEachComponent(out, [=](float x) { return roundN(x, digits); });
}

inline void truncColor(ColorVector& out) {
    forEachComponent(out, [](float x) { return std::trunc(x); });
}


////////////////////////////////////////////////////////////////////////////////

inline void addInto(float f, ColorVector& out) {
    forEachColorComponent(out, [=](float& x) { x += f; });
}
inline void addInto(ColorVector const& in, ColorVector& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o += i; });
}

inline void divideInto(float f, ColorVector& out) {
    forEachColorComponent(out, [=](float& x) { x /= (f ? f : 1); });
}
inline void divideInto(ColorVector const& in, ColorVector& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o /= i; });
}

inline void multiplyInto(float f, ColorVector& out) {
    forEachColorComponent(out, [=](float& x) { x *= f; });
}
inline void multiplyInto(ColorVector const& in, ColorVector& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o *= i; });
}

inline void powInto(float f, ColorVector& out) {
    forEachColorComponent(out, [=](float& x) { x = powFixed(x, f); });
}
inline void powInto(ColorVector const& in, ColorVector& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o = powFixed(o, i); });
}

inline void rdivideInto(float f, ColorVector& out) {
    forEachColorComponent(out, [=](float& x) { x = f / x; });
}
inline void rdivideInto(ColorVector const& in, ColorVector& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o = i / o; });
}

inline void rpowInto(float f, ColorVector& out) {
    forEachColorComponent(out, [=](float& x) { x = powFixed(f, x); });
}
inline void rpowInto(ColorVector const& in, ColorVector& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o = powFixed(o, i); });
}

inline void rsubtractInto(float f, ColorVector& out) {
    forEachColorComponent(out, [=](float& x) { x = f - x; });
}
inline void rsubtractInto(ColorVector const& in, ColorVector& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o = i - o; });
}

inline void subtractInto(float f, ColorVector& out) {
    forEachColorComponent(out, [=](float& x) { x -= f; });
}
inline void subtractInto(ColorVector const& in, ColorVector& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o -= i; });
}

inline void minInto(float f, ColorVector& out) {
    forEachColorComponent(out, [=](float& x) { x = std::min(f, x); });
}
inline void minInto(ColorVector const& in, ColorVector& out) {
    forEachColorComponent(in, out,
                          [](float i, float& o) { o = std::min(i, o); });
}

inline void maxInto(float f, ColorVector& out) {
    forEachColorComponent(out, [=](float& x) { x = std::max(f, x); });
}
inline void maxInto(ColorVector const& in, ColorVector& out) {
    forEachColorComponent(in, out,
                          [](float i, float& o) { o = std::max(i, o); });
}

inline size_t getSize(float x) {
    return std::numeric_limits<size_t>::max();
}

template <typename X>
size_t getSize(X const& x) {
    return x.size();
}

inline float getValue(float x, size_t, size_t) {
    return x;
}

template <typename X>
float_t getValue(X const& x, size_t i, size_t j) {
    return x[i][j];
}

template <typename X, typename Y, typename Function>
void doOver(X const& x, Y const& y, ColorVector& out, Function f) {
    auto size = std::min(getSize(x), getSize(y));
    out.resize(size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < 3; ++j)
            out[i][j] = f(getValue(x, i, j), getValue(y, i, j));
    }
}

template <typename X, typename Y>
void addOver(X const& x, Y const& y, ColorVector& out) {
    doOver(x, y, out, [](float x, float y) { return x + y; });
}

template <typename X, typename Y>
void divOver(X const& x, Y const& y, ColorVector& out) {
    doOver(x, y, out, [](float x, float y) { return x / y; });
}

template <typename X, typename Y>
void mulOver(X const& x, Y const& y, ColorVector& out) {
    doOver(x, y, out, [](float x, float y) { return x * y; });
}

template <typename X, typename Y>
void powOver(X const& x, Y const& y, ColorVector& out) {
    doOver(x, y, out, [](float x, float y) { return powFixed(x, y); });
}

template <typename X, typename Y>
void subOver(X const& x, Y const& y, ColorVector& out) {
    doOver(x, y, out, [](float x, float y) { return x - y; });
}

inline void hsvToRgbInto(ColorVector& out, Base b) {
    for (auto& c: out)
        c = hsvToRgb(c, b);
}

inline void rgbToHsvInto(ColorVector& out, Base b) {
    for (auto& c: out)
        c = rgbToHsv(c, b);
}

inline void appendInto(ColorVector const& in, ColorVector& out) {
    out.insert(out.end(), in.begin(), in.end());
}

inline void duplicateInto(size_t count, ColorVector& colors) {
    auto size = colors.size();
    colors.resize(size * count);

    for (auto i = colors.begin(); i < colors.end() - size; i += size)
        std::copy(i, i + size, i + size);
}

inline void clearInto(ColorVector& colors) {
    for (auto& c: colors)
        c = Color();
}

template <typename Function>
Color accumulate(ColorVector const& colors, Function f) {
    Color result{};
    auto first = true;
    for (auto& c: colors) {
        if (first) {
            first = false;
            result = c;
        } else {
            for (size_t i = 0; i < result.size(); ++i)
                result[i] = f(result[i], c[i]);
        }
    }
    return result;
}

inline Color maxColor(ColorVector const& colors) {
    return accumulate(colors, [](float x, float y) { return std::max(x, y); });
}

inline Color minColor(ColorVector const& colors) {
    return accumulate(colors, [](float x, float y) { return std::min(x, y); });
}

} // tada