 #pragma once

#include <algorithm>
#include <type_traits>

#include <timedata/base/enum.h>
#include <timedata/color/cython_inl.h>
#include <timedata/color/spread.h>

namespace timedata {
namespace color_list {

template <typename ColorList>
std::string toString(ColorList const& colors) {
    std::string result = "(";
    for (auto& c : colors) {
        if (result.size() > 1)
            result += ", ";
        auto s = color::toString(c);
        auto isTriple = isdigit(s[0]) or s[0] == '-';
        auto digit =  isTriple ? 1 : 0;
        result += "'("[digit];
        result += s;
        result += "')"[digit];
    }
    result += ")";
    return result;
}

template <typename ColorList>
NumberType<ColorList> comp(ColorList const& x, ColorList const& y) {
    auto size = std::min(x.size(), y.size());
    for (size_t i = 0; i < size; ++i) {
        for (size_t j = 0; j < y[i].size(); ++j) {
            if (auto d = x[i][j] - y[i][j])
                return d;
        }
    }

    return signum(x.size(), y.size());
}

template <typename ColorList>
NumberType<ColorList> comp(ValueType<ColorList> const& x, ColorList const& y) {
    for (size_t i = 0; i < y.size(); ++i) {
        for (size_t j = 0; j < y[i].size(); ++j) {
            if (auto d = x[j] - y[i][j])
                return d;
        }
    }

    return 0;
}

template <typename ColorList>
NumberType<ColorList> comp(NumberType<ColorList> x, ColorList const& y) {
    for (size_t i = 0; i < y.size(); ++i) {
        for (size_t j = 0; j < y[i].size(); ++j) {
            if (auto d = x - y[i][j])
                return d;
        }
    }

    return 0;
}

template <typename Input, typename ColorList>
bool compare(Input x, ColorList const& y, int richCmp) {
    return cmpToRichcmp(comp(x, y), richCmp);
}

using CNewColorList = color::CNewColor::List;
using CNewColorList255 = color::CNewColor255::List;
using CNewColorList256 = color::CNewColor256::List;

template <typename ColorList>
ColorList sliceOut(ColorList const& in, int begin, int end, int step) {
    return sliceVectorG(in, begin, end, step);
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
    return sliceIntoVectorG(in, out, begin, end, step);
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
void rotate(ColorList& out, int pos) {
    timedata::rotate(out, pos);
}

template <typename ColorList>
void round_cpp(ColorList& cl, size_t digits) {
    for (auto& c: cl) {
        for (auto& i: c)
            i = roundPython(*i, digits);
    }
}

template <typename ColorList>
void sort(ColorList& out) {
    using Color = ValueType<ColorList>;
    auto comp = [](Color const& x, Color const& y) { return cmp(x, y) < 0.0f; };
    std::sort(out.begin(), out.end(), comp);
}

template <typename ColorList>
void spreadAppend(ValueType<ColorList> const& end, size_t size, ColorList& out) {
    return timedata::spreadAppendG(end, size, out);
}

////////////////////////////////////////////////////////////////////////////////
template <typename T>
using Transform = typename std::add_pointer<T(T)>::type;

template <typename ColorList, typename Function>
void applyEach(ColorList& out, Function f) {
    for (auto& i: out)
        for (auto& j: i)
            i = f(i);
}

template <typename ColorList>
void applyEachF(ColorList& out, Transform<NumberType<ColorList>> f) {
    applyEach(out, f);
}

template <typename ColorList>
void math_abs(ColorList& out) {
    applyEach(out, std::abs);
}

template <typename ColorList>
void math_clear(ColorList& out) {
    out.clear();
}

template <typename ColorList> void math_floor(ColorList& out) {
    applyEach(out, std::floor);
}

template <typename ColorList>
void math_ceil(ColorList& out) {
    applyEach(out, std::ceil);
}

template <typename ColorList>
void math_invert(ColorList& out) {
    applyEach(out, [](NumberType<ColorList> c) { return c.invert(); });
}

template <typename ColorList>
void math_neg(ColorList& out) {
    applyEach(out, [](NumberType<ColorList> c) { return -c; });
}

template <typename ColorList>
void math_reverse(ColorList& out) {
    std::reverse(out.begin(), out.end());
}

template <typename ColorList>
void math_trunc(ColorList& out) {
    applyEach(out, std::trunc);
}

template <typename ColorList>
void math_zero(ColorList& out) {
    out.fill({});
}

////////////////////////////////////////////////////////////////////////////////

template <typename ColorList, typename Func>
void forEach(ColorList const& in, ColorList& out, Func f) {
    for (size_t i = 0; i < out.size(); ++i)
        for (size_t j = 0; j < out[i].size(); ++j)
            f(in[i][j], out[i][j]);
}

template <typename ColorList, typename Func>
void forEach(ValueType<ColorList> const& in, ColorList& out, Func f) {
    for (size_t i = 0; i < out.size(); ++i)
        for (size_t j = 0; j < out[i].size(); ++j)
            f(in, out[i][j]);
}

template <typename ColorList, typename Func>
void forEach(NumberType<ColorList> const& in, ColorList& out, Func f) {
    for (size_t i = 0; i < out.size(); ++i)
        for (size_t j = 0; j < out[i].size(); ++j)
            f(in, out[i][j]);
}

template <typename ColorList>
void resizeIf(ColorList const& in, ColorList& out) {
    if (out.size() < in.size())
        out.resize(in.size());
}

template <typename T, typename ColorList>
void resizeIf(T, ColorList&) {
}

template <typename Input, typename ColorList, typename Func>
void applyEach(Input const& in, ColorList& out, Func f) {
    using Number = NumberType<ColorList>;
    resizeIf(in, out);
    forEach(in, out, [&f](Number x, Number &y) { y = f(x); });
}

template <typename Input, typename ColorList>
void math_add(Input const& in, ColorList& out) {
    using Number = NumberType<ColorList>;
    applyEach(in, out, [](Number x, Number y) { return x + y; });
}

template <typename Input, typename ColorList>
void math_div(Input const& in, ColorList& out) {
    using Number = NumberType<ColorList>;
    applyEach(in, out, [](Number x, Number y) { return pythonDiv(x, y); });
}

template <typename Input, typename ColorList>
void math_rdiv(Input const& in, ColorList& out) {
    using Number = NumberType<ColorList>;
    applyEach(in, out, [](Number x, Number y) { return pythonDiv(y, x); });
}

template <typename Input, typename ColorList>
void math_mul(Input const& in, ColorList& out) {
    using Number = NumberType<ColorList>;
    applyEach(in, out, [](Number x, Number y) { return x * y; });
}

template <typename Input, typename ColorList>
void math_pow(Input const& in, ColorList& out) {
    using Number = NumberType<ColorList>;
    applyEach(in, out, [](Number x, Number y) { return std::pow(x, y); });
}

template <typename Input, typename ColorList>
void math_rpow(Input const& in, ColorList& out) {
    using Number = NumberType<ColorList>;
    applyEach(in, out, [](Number x, Number y) { return std::pow(y, x); });
}

template <typename Input, typename ColorList>
void math_sub(Input const& in, ColorList& out) {
    using Number = NumberType<ColorList>;
    applyEach(in, out, [](Number x, Number y) { return x - y; });
}

template <typename Input, typename ColorList>
void math_rsub(Input const& in, ColorList& out) {
    using Number = NumberType<ColorList>;
    applyEach(in, out, [](Number x, Number y) { return y - x; });
}

template <typename Input, typename ColorList>
void math_min_limit(Input const& in, ColorList& out) {
    using Number = NumberType<ColorList>;
    applyEach(in, out, [](Number x, Number y) { return std::max(x, y); });
}

template <typename Input, typename ColorList>
void math_max_limit(Input const& in, ColorList& out) {
    using Number = NumberType<ColorList>;
    applyEach(in, out, [](Number x, Number y) { return std::min(x, y); });
}

template <typename ColorList>
NumberType<ColorList> distance2(ColorList const& x, ColorList const& y) {
    NumberType<ColorList> result = 0.0f;
    auto xShorter = x.size() < y.size();
    auto& shorter = xShorter ? x : y;
    auto& longer = xShorter ? y : x;

    size_t i = 0;
    for (; i < shorter.size(); ++i) {
        for (auto j = 0; j < longer[i].size(); ++j) {
            auto d = longer[i][j] - shorter[i][j];
            result += d * d;
        }
    }

    for (; i < longer.size(); ++i) {
        for (auto j = 0; j < longer[i].size(); ++j) {
            result += longer[i][j] * longer[i][j];
        }
    }

    return result;
}

template <typename ColorList>
NumberType<ColorList> distance2(
        ValueType<ColorList> const& x, ColorList const& y) {
    NumberType<ColorList> result = 0.0f;
    for (size_t i = 0; i < y.size(); ++i) {
        for (auto j = 0; j < y[i].size(); ++j) {
            auto d = x[j] - y[i][j];
            result += d * d;
        }
    }
    return result;
}

template <typename ColorList>
NumberType<ColorList> distance2(NumberType<ColorList> x, ColorList const& y) {
    NumberType<ColorList> result = 0.0f;
    for (size_t i = 0; i < y.size(); ++i) {
        for (auto j = 0; j < y[i].size(); ++j) {
            auto d = x - y[i][j];
            result += d * d;
        }
    }
    return result;
}

template <typename Input, typename ColorList>
NumberType<ColorList> distance(Input const& x, ColorList const& y) {
    return std::sqrt(distance2(x, y));
}

template <typename ColorList>
void magic_add(ColorList const& in, ColorList& out) {
    appendInto(in, out);
}

template <typename ColorList>
void magic_mul(size_t size, ColorList& out) {
    duplicateInto(size< out);
}

} // color_list
} // timedata
