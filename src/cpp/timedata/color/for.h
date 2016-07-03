 #pragma once

namespace timedata {
namespace color_list {

template <typename ColorList, typename Function>
void forParts1(ColorList const& in, ColorList& out, Function f) {
    if (out.size() < in.size())
        out.resize(in.size());
    for (size_t i = 0; i < in.size(); ++i) {
        for (size_t j = 0; j < in[i].size(); ++j)
            out[i][j] = f(in[i][j]);
    }
}

template <typename ColorList, typename Function>
void forParts1(ColorList& out, Function f) {
    forParts1(out, out, f);
}

template <typename ColorList, typename Function, typename Getter>
void forParts2Imp(ColorList const& in, ColorList& out, Function f, Getter get) {
    for (size_t i = 0; i < in.size(); ++i) {
        for (size_t j = 0; j < in[i].size(); ++j)
            out[i][j] = f(in[i][j], get(i, j));
    }
}

template <typename ColorList, typename Function>
void forParts2(ColorList const& in, ColorList const& in2,
               ColorList& out, Function f) {
    if (out.size() < in.size())
        out.resize(in.size());
    forParts2Impl(in, out, f, [&](size_t i, size_t j) { return in2[i][j]; });
}

template <typename ColorList, typename Function>
void forParts2(ColorList const& in, ValueType<ColorList> const& in2,
               ColorList& out, Function f) {
    forParts2Impl(in, out, f, [&](size_t, size_t j) { return in2[j]; });
}

template <typename ColorList, typename Function>
void forParts2(ColorList const& in, NumberType<ColorList> const& in2,
               ColorList& out, Function f) {
    forParts2Impl(in, out, f, [&](size_t, size_t) { return in2; });
}

template <typename Input, typename ColorList, typename Function>
void forParts2(Input in2, ColorList& out, Function f) {
    forParts2(out, in2, out, f);
}

// Hopefully obsolete.
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
            f(in[j], out[i][j]);
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
    // using Number = NumberType<ColorList>;
    using Number = RangedType<ColorList>;
    resizeIf(in, out);
    forEach(in, out, [&f](Number x, Number &y) { y = f(x, y); });
}

} // color_list
} // timedata
