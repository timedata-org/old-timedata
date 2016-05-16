#pragma once

#include <tdsp/color/colorList.h>
#include <tdsp/base/make.h>
#include <tdsp/base/math_inl.h>
#include <tdsp/color/names_inl.h>
#include <tdsp/signal/slice.h>

namespace tdsp {

inline
ColorList duplicate(ColorList const& v, size_t count) {
    ColorList result;
    for (size_t i = 0; i < count; ++i)
        result.insert(result.end(), v.begin(), v.end());
    return result;
}

inline
void reverse(ColorList& v) {
    std::reverse(v.begin(), v.end());
}

inline std::string toString(ColorList const& colors, Base base) {
    std::string result = "(";
    for (auto& c : colors) {
        if (result.size() > 1)
            result += ", ";
        auto s = colorToString(c, base);
        result += "'("[isdigit(s[0])];
        result += s;
        result += "')"[isdigit(s[0])];
    }
    result += ")";
    return result;
}

inline
ColorList sliceVector(
        ColorList const& in, int begin, int end, int step) {
    // TODO: is this used?
    auto slice = make<Slice>(begin, end, step);
    ColorList out;
    forEach(slice, [&](int j) { out.push_back(in[j]); });
    return out;
}

inline
bool sliceIntoVector(ColorList const& in, ColorList& out,
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
void forEachColorComponent(ColorList& colors, Function f) {
    // WRONG!
    for (auto& color : colors)
        for (auto& c : color)
            f(c);
}

template <typename Function>
void forEachComponent(ColorList& colors, Function f) {
    for (auto& color : colors)
        for (auto& c : color)
            c = f(c);
}

template <typename Function>
void forEachColorComponent(ColorList const& in, ColorList& out, Function f) {
    if (out.size() < in.size())
        out.resize(in.size());

    for (size_t i = 0; i < in.size(); ++i)
        for (size_t j = 0; j < in[i].size(); ++j)
            f(in[i][j], out[i][j]);
}

inline void absColor(ColorList& out) {
    forEachComponent(out, [](float x) { return std::abs(x); });
}

inline void ceilColor(ColorList& out) {
    forEachComponent(out, [](float x) { return std::ceil(x); });
}

inline void floorColor(ColorList& out) {
    forEachComponent(out, [](float x) { return std::floor(x); });
}

inline void invertColor(ColorList& out) {
    forEachComponent(out, [](float x) { return (x > 0 ? 1.0 : -1.0) - x; });
}

inline void negateColor(ColorList& out) {
    forEachComponent(out, [](float x) { return -x; });
}

inline void roundColor(ColorList& out) {
    forEachComponent(out, [](float x) { return round(x); });
}

inline void truncColor(ColorList& out) {
    forEachComponent(out, [](float x) { return std::trunc(x); });
}


////////////////////////////////////////////////////////////////////////////////

inline void addInto(float f, ColorList& out) {
    forEachColorComponent(out, [=](float& x) { x += f; });
}
inline void addInto(ColorList const& in, ColorList& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o += i; });
}

inline void divideInto(float f, ColorList& out) {
    forEachColorComponent(out, [=](float& x) { x /= f; });
}
inline void divideInto(ColorList const& in, ColorList& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o /= i; });
}

inline void multiplyInto(float f, ColorList& out) {
    forEachColorComponent(out, [=](float& x) { x *= f; });
}
inline void multiplyInto(ColorList const& in, ColorList& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o *= i; });
}

inline void powInto(float f, ColorList& out) {
    forEachColorComponent(out, [=](float& x) { x = pow(x, f); });
}
inline void powInto(ColorList const& in, ColorList& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o = pow(o, i); });
}

inline void rdivideInto(float f, ColorList& out) {
    forEachColorComponent(out, [=](float& x) { x = f / x; });
}
inline void rdivideInto(ColorList const& in, ColorList& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o = i / o; });
}

inline void rpowInto(float f, ColorList& out) {
    forEachColorComponent(out, [=](float& x) { x = pow(f, x); });
}
inline void rpowInto(ColorList const& in, ColorList& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o = pow(o, i); });
}

inline void rsubtractInto(float f, ColorList& out) {
    forEachColorComponent(out, [=](float& x) { x = f - x; });
}
inline void rsubtractInto(ColorList const& in, ColorList& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o = i - o; });
}

inline void subtractInto(float f, ColorList& out) {
    forEachColorComponent(out, [=](float& x) { x -= f; });
}
inline void subtractInto(ColorList const& in, ColorList& out) {
    forEachColorComponent(in, out, [](float i, float& o) { o -= i; });
}

inline void minInto(float f, ColorList& out) {
    forEachColorComponent(out, [=](float& x) { x = std::min(f, x); });
}
inline void minInto(ColorList const& in, ColorList& out) {
    forEachColorComponent(in, out,
                          [](float i, float& o) { o = std::min(i, o); });
}

inline void maxInto(float f, ColorList& out) {
    forEachColorComponent(out, [=](float& x) { x = std::max(f, x); });
}
inline void maxInto(ColorList const& in, ColorList& out) {
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
void doOver(X const& x, Y const& y, ColorList& out, Function f) {
    auto size = std::min(getSize(x), getSize(y));
    out.resize(size);
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < 3; ++j)
            out[i][j] = f(getValue(x, i, j), getValue(y, i, j));
    }
}

template <typename X, typename Y>
void addOver(X const& x, Y const& y, ColorList& out) {
    doOver(x, y, out, [](float x, float y) { return x + y; });
}

template <typename X, typename Y>
void divOver(X const& x, Y const& y, ColorList& out) {
    doOver(x, y, out, [](float x, float y) { return x / y; });
}

template <typename X, typename Y>
void mulOver(X const& x, Y const& y, ColorList& out) {
    doOver(x, y, out, [](float x, float y) { return x * y; });
}

template <typename X, typename Y>
void powOver(X const& x, Y const& y, ColorList& out) {
    doOver(x, y, out, [](float x, float y) { return pow(x, y); });
}

template <typename X, typename Y>
void subOver(X const& x, Y const& y, ColorList& out) {
    doOver(x, y, out, [](float x, float y) { return x - y; });
}

} // tdsp
