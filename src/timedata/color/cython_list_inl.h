#pragma once

#include <algorithm>
#include <timedata/color/cython_inl.h>
#include <timedata/color/spread.h>

namespace timedata {
namespace color {


using ColorListCpp = std::vector<ColorCpp>;
using ColorListCpp255 = std::vector<ColorCpp255>;
using ColorListCpp256 = std::vector<ColorCpp256>;

template <typename ColorList>
size_t count(ColorList const& c, ValueType<ColorList> const& s) {
    return std::count(c.begin(), c.end(), s);
}

template <typename ColorList>
void extend(ColorList const& in, ColorList& out) {
    in.insert(in.end(), out.begin(), out.end());
}

template <typename ColorList>
int index(ColorList const& c, ValueType<ColorList> const& s) {
    auto i = std::find(c.begin(), c.end(), s);
    return i != c.end() ? c - c.begin() : -1;
}

template <typename ColorList>
void insert(int key, ValueType<ColorList> const& color, ColorList& out) {
    if (not fixKey(key, out.size()))
        key = std::max(0, std::min(static_cast<int>(out.size()), key));
    out.insert(out.begin() + key, color);
}

template <typename ColorList>
bool pop(ColorList& colors, int key, ValueType<ColorList>& result) {
    if (not fixKey(key, colors.size()))
        return false;
    result = colors[key];
    colors.erase(colors.begin() + key);
    return true;
}

template <typename ColorList>
void rotate(ColorList& colors, int pos) {
    timedata::rotate(colors, pos);
}

template <typename ColorList>
void sort(ColorList const& colors) {
    using Color = ValueType<ColorList>;
    auto comp = [](Color const& x, Color const& y) { return cmp(x, y) < 0.0f; };
    std::sort(colors.begin(), colors.end(), comp);
}

template <typename ColorList>
void round_cpp(ColorList& cl, size_t digits) {
    for (auto& c: cl) {
        for (auto& i: c)
            i = roundPython(*i, digits);
    }
}

template <typename ColorList>
ValueType<ColorList> min_cpp(ColorList const& cl) {
    using Color = ValueType<ColorList>;
    using value_type = ValueType<Color>;

    Color result;
    result.fill(std::numeric_limits<value_type>::infinity());
    for (auto& c: cl) {
        for (size_t i = 0; i < c.size(); ++i)
            result[i] = std::min(result[i], c[i]);
    }
    return result;
}

template <typename ColorList>
ValueType<ColorList> max_cpp(ColorList const& cl) {
    using Color = ValueType<ColorList>;
    using value_type = ValueType<Color>;

    Color result;
    result.fill(std::numeric_limits<value_type>::infinity());
    for (auto& c: cl) {
        for (size_t i = 0; i < c.size(); ++i)
            result[i] = std::max(result[i], c[i]);
    }
    return result;
}

template <typename ColorList>
void spreadAppend(ColorList& out, size_t size, ValueType<ColorList> const& end) {
    return timedata::spreadAppend(out, size, end);
}

template <typename ColorList>
bool sliceInto(
         ColorList const& in, ColorList& out, int begin, int end, int step) {
    return sliceIntoVector(in, out, being, end, step);
}

template <typename ColorList>
ColorList sliceOut(ColorList const& colors, int begin, int end, int step) {
    return sliceVector(in, begin, end, step);
}

template <typename ColorList>
void math_abs(ColorList& colors) {
}

template <typename ColorList>
void math_clear(ColorList& colors) {
}

template <typename ColorList>
void math_floor(ColorList& colors) {
}

template <typename ColorList>
void math_ceil(ColorList& colors) {
}

template <typename ColorList>
void math_invert(ColorList& colors) {
}

template <typename ColorList>
void math_neg(ColorList& colors) {
}

template <typename ColorList>
void math_reverse(ColorList& colors) {
}

template <typename ColorList>
void math_trunc(ColorList& colors) {
}

template <typename ColorList>
void math_zero(ColorList& colors) {
}

template <typename ColorList>
void math_add(float, ColorList& colors) {
}

template <typename ColorList>
void math_add(ColorList const& in, ColorList& out) {
}

template <typename ColorList>
void math_div(float, ColorList& colors) {
}

template <typename ColorList>
void math_div(ColorList const& in, ColorList& out) {
}

 template <typename ColorList>
void math_mul(float, ColorList& colors) {
}

template <typename ColorList>
void math_mul(ColorList const& in, ColorList& out) {
}

template <typename ColorList>
void math_pow(float, ColorList& colors) {
}

template <typename ColorList>
void math_pow(ColorList const& in, ColorList& out) {
}

template <typename ColorList>
void math_sub(float, ColorList& colors) {
}

template <typename ColorList>
void math_sub(ColorList const& in, ColorList& out) {
}

template <typename ColorList>
void math_rdiv(float, ColorList& colors) {
}

template <typename ColorList>
void math_rdiv(ColorList const& in, ColorList& out) {
}

template <typename ColorList>
void math_rpow(float, ColorList& colors) {
}

template <typename ColorList>
void math_rpow(ColorList const& in, ColorList& out) {
}

template <typename ColorList>
void math_rsub(float, ColorList& colors) {
}

template <typename ColorList>
void math_rsub(ColorList const& in, ColorList& out) {
}

template <typename ColorList>
ColorList limit_min(ColorList const& in, ColorList& out) {
}

template <typename ColorList>
ColorList limit_max(ColorList const& in, ColorList& out) {

}

template <typename ColorList>
float distance(ColorList const& x, ColorList const& y) {
    return timedata::distance(x, y);
}

template <typename ColorList>
float distance2(ColorList const& x, ColorList const& y) {
    return timedata::distance2(x, y);
}

template <typename ColorList>
void magic_add(ColorList const& in, ColorList& out) {
    appendInto(in, out);
}

template <typename ColorList>
void magic_mul(size_t size, ColorList& colors) {
    duplicateInto(size< colors);
}

} // color
} // timedata
