#pragma once

#include <algorithm>
#include <cstddef>
#include <type_traits>

#include <timedata/base/enum.h>
#include <timedata/base/make.h>
#include <timedata/base/math_inl.h>
#include <timedata/color/cython_inl.h>
#include <timedata/color/for.h>
#include <timedata/color/spread.h>
#include <timedata/signal/slice.h>

namespace timedata {
namespace color_list {

using CColorListRGB = color::CColorRGB::List;
using CColorListHSV = color::CColorHSV::List;
using CColorListHSL = color::CColorHSL::List;
using CColorListXYZ = color::CColorXYZ::List;
using CColorListYIQ = color::CColorYIQ::List;
using CColorListYUV = color::CColorYUV::List;

using CColorListRGB255 = color::CColorRGB255::List;
using CColorListRGB256 = color::CColorRGB256::List;

using CIndexList = timedata::CIndexList;

template <typename Color>
void toStringItem(Color c, std::string& result) {
    auto s = color::toString(c);
    auto isTriple = s.find(",") != std::string::npos;
    auto digit = isTriple ? 1 : 0;
    result += "'("[digit];
    result += s;
    result += "')"[digit];
}

template <>
inline void toStringItem(int x, std::string& result) {
    result += std::to_string(x);
}

template <typename ColorList>
std::string toString(ColorList const& colors) {
    std::string result = "(";
    for (auto& c : colors) {
        if (result.size() > 1)
            result += ", ";
        toStringItem(c, result);
    }
    result += ")";
    return result;
}

template <typename ColorList>
float compare(ColorList const& x, ColorList const& y) {
    auto size = std::min(x.size(), y.size());
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < y[i].size(); ++j) {
            if (auto d = x[i][j] - y[i][j])
                return d;
        }
    }

    return static_cast<NumberType<ColorList>>(signum(x.size(), y.size()));
}

template <>
float compare(CIndexList const& x, CIndexList const& y) {
    auto size = std::min(x.size(), y.size());
    for (size_t i = 0; i < size; ++i) {
        if (auto d = x[i] - y[i])
            return float(d);
    }

    return float(signum(x.size(), y.size()));
}

template <typename ColorList>
float compare(ValueType<ColorList> const& x, ColorList const& y) {
    for (size_t i = 0; i < y.size(); ++i) {
        for (size_t j = 0; j < y[i].size(); ++j) {
            if (auto d = x[j] - y[i][j])
                return d;
        }
    }

    return 0;
}

template <>
float compare(int const& x, CIndexList const& y) {
    for (size_t i = 0; i < y.size(); ++i) {
        if (auto d = x - y[i])
            return float(d);
    }

    return 0.0f;
}

inline bool cmpToRichcmp(float diff, int richcmp) {
    return timedata::cmpToRichcmp(diff, richcmp);
}

template <typename ColorList>
float compare(NumberType<ColorList> x, ColorList const& y) {
    for (size_t i = 0; i < y.size(); ++i) {
        for (size_t j = 0; j < y[i].size(); ++j) {
            if (auto d = x - y[i][j])
                return d;
        }
    }

    return 0;
}

template <typename ColorVector>
ColorVector sliceOut(ColorVector const& in, int begin, int end, int step) {
    auto slice = make<Slice>(begin, end, step);
    ColorVector out;
    forEach(slice, [&](int j) { out.push_back(in[j]); });
    return out;
}

template <typename ColorVector>
void erase(int key, ColorVector& v) {
    v.erase(v.begin() + key);
}

template <typename ColorVector>
void sliceDelete(ColorVector& colors, int begin, int end, int step) {
    auto b = static_cast<size_t>(begin);
    if (step < 0) {
        std::swap(begin, end);
        step = -step;
    }
    size_t offset = 0;
    for (size_t i = 0; i < colors.size(); ++i) {
        if (i == b) {
            b += step;
            offset += 1;
        } else if (offset) {
            colors[i - offset] = colors[i];
        }
    }
    if (offset)
        colors.resize(colors.size() - offset);
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
    result.fill(-std::numeric_limits<value_type>::infinity());
    for (auto& c: cl) {
        for (size_t i = 0; i < c.size(); ++i)
            result[i] = std::max(result[i], c[i]);
    }
    return result;
}

////////////////////////////////////////////////////////////////////////////////

inline
bool resolvePythonIndex(int& index, size_t size) {
    return timedata::color::resolvePythonIndex(index, size);
}

template <typename ColorList>
bool pop(ColorList& out, int key, ValueType<ColorList>& result) {
    if (not resolvePythonIndex(key, out.size()))
        return false;
    result = out[key];
    out.erase(out.begin() + key);
    return true;
}

template <typename ColorList>
bool sliceInto(
         ColorList const& in, ColorList& out, int begin, int end, int step) {
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

////////////////////////////////////////////////////////////////////////////////

template <typename ColorList>
int index(ColorList const& c, ValueType<ColorList> const& s) {
    auto i = std::find(c.begin(), c.end(), s);
    return i != c.end() ? (i - c.begin()) : -1;
}

////////////////////////////////////////////////////////////////////////////////

template <typename ColorList>
size_t count(ColorList const& c, ValueType<ColorList> const& s) {
    return std::count(c.begin(), c.end(), s);
}

////////////////////////////////////////////////////////////////////////////////

template <typename ColorList>
void extend(ColorList const& in, ColorList& out) {
    out.insert(out.end(), in.begin(), in.end());
}


template <typename ColorList>
void insert(int key, ValueType<ColorList> const& color, ColorList& out) {
    if (not resolvePythonIndex(key, out.size()))
        key = std::max(0, std::min(static_cast<int>(out.size()), key));
    out.insert(out.begin() + key, color);
}

template <typename ColorList>
bool remap_to(CIndexList const& remap, ColorList const& in, ColorList& out) {
    if (out.size() < remap.size())
        out.resize(remap.size());
    for (size_t i = 0; i < remap.size(); ++i) {
        auto index = remap[i];
        if (not resolvePythonIndex(index, in.size()))
            return false;
        out[i] = in[index];
    }
    return true;
}

template <typename ColorList>
void rotate(ColorList& out, int pos) {
    timedata::rotate(out, pos);
}

template <typename ColorList>
void rotate(ColorList const& in, ColorList& out, int pos) {
    resizeIf(in, out);
    pos = pos % in.size();
    if (pos < 0)
        pos += in.size();
    std::rotate_copy(in.begin(), in.begin() + pos, in.end(), out.begin());
}

template <typename ColorList>
void round_cpp(ColorList& out, size_t digits) {
    using T = NumberType<ColorList>;
    forParts1(out, [=](T x) { return roundPython(x, digits); });
}

template <typename ColorList>
void round_cpp(ColorList& in, ColorList& out, size_t digits) {
    using T = NumberType<ColorList>;
    forParts1(in, out, [=](T x) { return roundPython(x, digits); });
}

template <typename ColorList>
void sort(ColorList& out) {
    std::sort(out.begin(), out.end());
}

template <typename ColorList>
void sort(ColorList const& i, ColorList& o, bool reversed) {
    resizeIf(i, o);
    if (not reversed)
        std::partial_sort_copy(i.begin(), i.end(), o.begin(), o.end());
    else
        std::partial_sort_copy(i.begin(), i.end(), o.rbegin(), o.rend());
}

template <typename ColorList>
void spreadAppend(ValueType<ColorList> const& end, size_t size,
                  ColorList& out) {
    return timedata::spreadAppendG(end, size, out);
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
using Transform = typename std::add_pointer<T(T)>::type;

template <typename ColorList, typename Function>
void applyEach(ColorList& out, Function f) {
    for (auto& i: out)
        for (auto& j: i)
            j = f(j);
}

template <typename ColorList>
void forParts1F(ColorList const& in, ColorList& out,
                Transform<NumberType<ColorList>> f) {
    forParts1(in, out, f);
}

template <typename ColorList>
void math_abs(ColorList const& in, ColorList& out) {
    forParts1F(in, out, std::abs);
}

template <typename ColorList>
void math_floor(ColorList const& in, ColorList& out) {
    forParts1F(in, out, std::floor);
}

template <typename ColorList>
void math_ceil(ColorList const& in, ColorList& out) {
    forParts1F(in, out, std::ceil);
}

template <typename ColorList>
void math_invert(ColorList const& in, ColorList& out) {
    using Ranged = typename ColorList::ranged_type;
    forParts1(in, out, [](Ranged c) { return c.invert(); });
}

template <typename ColorList>
void math_neg(ColorList const& in, ColorList& out) {
    forParts1(in, out, [](NumberType<ColorList> c) { return -c; });
}

template <typename ColorList>
void math_reverse(ColorList const& in, ColorList& out) {
    resizeIf(in, out);
    if (&out == &in)
        std::reverse(out.begin(), out.end());
    else
        std::reverse_copy(in.begin(), in.end(), out.begin());
}

template <typename ColorList>
void math_trunc(ColorList const& in, ColorList& out) {
    forParts1F(in, out, std::trunc);
}

////////////////////////////////////////////////////////////////////////////////

template <typename ColorList>
void math_clear(ColorList& out) {
    out.clear();
}

template <typename ColorList>
void math_zero(ColorList& out) {
    std::fill(out.begin(), out.end(), ValueType<ColorList>{});
}

////////////////////////////////////////////////////////////////////////////////

template <typename Input, typename ColorList>
void math_add(ColorList const& in, Input const& in2, ColorList& out) {
    using Number = RangedType<ColorList>;
     forParts2(in, in2, out, [](Number x, Number y) { return x + y; });
}

template <typename Input, typename ColorList>
void math_div(ColorList const& in, Input const& in2, ColorList& out) {
    using Number = NumberType<ColorList>;
    forParts2(in, in2, out, [](Number x, Number y) { return divPython(y, x); });
}

template <typename Input, typename ColorList>
void math_rdiv(ColorList const& in, Input const& in2, ColorList& out) {
    using Number = NumberType<ColorList>;
    forParts2(in, in2, out, [](Number x, Number y) { return divPython(x, y); });
}

template <typename Input, typename ColorList>
void math_mul(ColorList const& in, Input const& in2, ColorList& out) {
    using Number = NumberType<ColorList>;
    forParts2(in, in2, out, [](Number x, Number y) { return x * y; });
}

template <typename Input, typename ColorList>
void math_pow(ColorList const& in, Input const& in2, ColorList& out) {
    using Number = NumberType<ColorList>;
    forParts2(in, in2, out, [](Number x, Number y) { return powPython(y, x); });
}

template <typename Input, typename ColorList>
void math_rpow(ColorList const& in, Input const& in2, ColorList& out) {
    using Number = NumberType<ColorList>;
    forParts2(in, in2, out, [](Number x, Number y) { return powPython(x, y); });
}

template <typename Input, typename ColorList>
void math_sub(ColorList const& in, Input const& in2, ColorList& out) {
    using Number = NumberType<ColorList>;
    forParts2(in, in2, out, [](Number x, Number y) { return x - y; });
}

template <typename Input, typename ColorList>
void math_rsub(ColorList const& in, Input const& in2, ColorList& out) {
    using Number = NumberType<ColorList>;
    forParts2(in, in2, out, [](Number x, Number y) { return y - x; });
}

template <typename Input, typename ColorList>
void math_min_limit(ColorList const& in, Input const& in2, ColorList& out) {
    using Number = NumberType<ColorList>;
    forParts2(in, in2, out, [](Number x, Number y) { return std::max(x, y); });
}

template <typename Input, typename ColorList>
void math_max_limit(ColorList const& in, Input const& in2, ColorList& out) {
    using Number = NumberType<ColorList>;
    forParts2(in, in2, out, [](Number x, Number y) { return std::min(x, y); });
}

template <typename ColorList>
float distance2(ColorList const& x, ColorList const& y) {
    NumberType<ColorList> result = 0.0f;
    auto xShorter = x.size() < y.size();
    auto& shorter = xShorter ? x : y;
    auto& longer = xShorter ? y : x;

    size_t i = 0;
    for (; i < shorter.size(); ++i) {
        for (size_t j = 0; j < longer[i].size(); ++j) {
            auto d = longer[i][j] - shorter[i][j];
            result += d * d;
        }
    }

    for (; i < longer.size(); ++i) {
        for (size_t j = 0; j < longer[i].size(); ++j) {
            result += longer[i][j] * longer[i][j];
        }
    }

    return result;
}

template <>
float distance2(CIndexList const& x, CIndexList const& y) {
    float result = 0.0f;
    auto xShorter = x.size() < y.size();
    auto& shorter = xShorter ? x : y;
    auto& longer = xShorter ? y : x;

    size_t i = 0;
    for (; i < shorter.size(); ++i) {
        auto d = longer[i] - shorter[i];
        result += d * d;
    }

    for (; i < longer.size(); ++i)
        result += longer[i] * longer[i];

    return result;
}

template <typename ColorList>
NumberType<ColorList> distance2(
        ValueType<ColorList> const& x, ColorList const& y) {
    NumberType<ColorList> result = 0.0f;
    for (size_t i = 0; i < y.size(); ++i) {
        for (size_t j = 0; j < y[i].size(); ++j) {
            auto d = x[j] - y[i][j];
            result += d * d;
        }
    }
    return result;
}

inline
float distance2(float x, CIndexList const& y) {
    float result = 0.0f;
    for (size_t i = 0; i < y.size(); ++i) {
        auto d = x - y[i];
        result += d * d;
    }

    return result;
}

template <typename ColorList>
NumberType<ColorList> distance2(NumberType<ColorList> x, ColorList const& y) {
    NumberType<ColorList> result = 0.0f;
    for (size_t i = 0; i < y.size(); ++i) {
        for (size_t j = 0; j < y[i].size(); ++j) {
            auto d = x - y[i][j];
            result += d * d;
        }
    }
    return result;
}

template <typename Input, typename ColorList>
NumberType<ColorList> distance(Input x, ColorList const& y) {
    return std::sqrt(distance2(x, y));
}

inline
float distance(CIndexList const& x, CIndexList const& y) {
    return std::sqrt(distance2(x, y));
}

inline
float distance(size_t x, CIndexList const& y) {
    return std::sqrt(distance2(x, y));
}

template <typename ColorList>
void magic_add(ColorList const& in, ColorList& out) {
    out.insert(out.end(), in.begin(), in.end());
}

template <typename ColorVector>
void magic_mul(size_t count, ColorVector& colors) {
    auto size = colors.size();
    colors.resize(size * count);

    for (auto i = colors.begin(); i < colors.end() - size; i += size)
        std::copy(i, i + size, i + size);
}

template <typename ColorVector>
void shuffle(ColorVector& colors) {
    std::random_shuffle(colors.begin(), colors.end());
}

} // color_list
} // timedata
