#pragma once

#include <limits>

#include <tdsp/color/operation.h>
#include <tdsp/color/colorList_inl.h>

namespace tdsp {
namespace operation {
namespace detail {

/// Helper functions to let us treat integers and lists the same way.
inline float get(float x, size_t, size_t) {
    return x;
}

inline float get(ColorList const& x, size_t i, size_t j) {
    return x[i][j];
}

/*
 Unary functions.
*/

template <Unary> float run(float);

template <> float run<Unary::ABS>(float x)    { return std::abs(x); }
template <> float run<Unary::CLEAR>(float)    { return 0.0f; }
template <> float run<Unary::INVERT>(float x) { return invert(x); }
template <> float run<Unary::NEGATE>(float x) { return -x; }

template <Unary op>
void apply(ColorList const& in, ColorList& out) {
    for (auto i = 0; i < out.size(); ++i)
        for (auto j = 0; j < 3; ++j)
            out[i][j] = run<op>(get(in, i, j));
}

template <Unary op>
void apply(ColorList& out) {
    for (auto& color: out)
        for (auto& c: color)
            c = run<op>(c);
}

inline void run(Unary op, ColorList& out) {
    switch (op) {
        case Unary::ABS:    return apply<Unary::ABS>(out);
        case Unary::CLEAR:  return apply<Unary::CLEAR>(out);
        case Unary::INVERT: return apply<Unary::INVERT>(out);
        case Unary::NEGATE: return apply<Unary::NEGATE>(out);
    }
}

template <typename Input>
void run(Unary op, Input const& in, ColorList& out) {
    switch (op) {
        case Unary::ABS:    return apply<Unary::ABS>(in, out);
        case Unary::CLEAR:  return apply<Unary::CLEAR>(in, out);
        case Unary::INVERT: return apply<Unary::INVERT>(in, out);
        case Unary::NEGATE: return apply<Unary::NEGATE>(in, out);
    }
}

/*
 Binary functions.
*/

template <Binary> float run(float x, float y);

template <> float run<Binary::ADD>(float x, float y) { return x + y; }
template <> float run<Binary::DIV>(float x, float y) { return x / y; }
template <> float run<Binary::MAX>(float x, float y) { return std::max(x, y); }
template <> float run<Binary::MIN>(float x, float y) { return std::min(x, y); }
template <> float run<Binary::MUL>(float x, float y) { return x * y; }
template <> float run<Binary::POW>(float x, float y) { return pow(x, y); }
template <> float run<Binary::SUB>(float x, float y) { return x - y; }

template <Binary op, Side side, typename X, typename Y>
void run(size_t size, X const& x, Y const& y, ColorList& out) {
    for (size_t i = 0; i < size; ++i) {
        for (auto j = 0; j < 3; ++j) {
            auto a = get(x, i, j), b = get(y, i, j);
            out[i][j] = (side == Side::LEFT) ? run<op>(a, b) : run<op>(b, a);
        }
    }
}

template <Side side, typename X, typename Y>
void run(Binary op, size_t size, X const& x, Y const& y, ColorList& out) {
    switch (op) {
        case Binary::ADD: return run<Binary::ADD, side>(size, x, y, out);
        case Binary::DIV: return run<Binary::DIV, side>(size, x, y, out);
        case Binary::MAX: return run<Binary::MAX, side>(size, x, y, out);
        case Binary::MIN: return run<Binary::MIN, side>(size, x, y, out);
        case Binary::MUL: return run<Binary::MUL, side>(size, x, y, out);
        case Binary::POW: return run<Binary::POW, side>(size, x, y, out);
        case Binary::SUB: return run<Binary::SUB, side>(size, x, y, out);
    }
}

template <typename X, typename Y>
void run(Side s, Binary op, size_t size, X const& x, Y const& y, ColorList& o) {
    if (s == Side::LEFT)
        run<Side::LEFT>(op, size, x, y, o);
    else
        run<Side::RIGHT>(op, size, x, y, o);
}

} // namespace detail

inline void runInto(Unary op, ColorList& out) {
    return detail::run(op, out);
}

inline void runTogether(Unary op, ColorList const& in, ColorList& out) {
    out.resize(in.size());
    return detail::run(op, in, out);
}

inline void runInto(Binary op, Side side, float x, ColorList& out) {
    detail::run(side, op, out.size(), x, out, out);
}

inline void runInto(Binary op, Side side, ColorList const& x, ColorList& out) {
    detail::run(side, op, std::min(x.size(), out.size()), x, out, out);
}

inline void runTogether(Binary op, Side side,
                        ColorList const& x, float y,
                        ColorList& out) {
    out.resize(x.size());
    detail::run(side, op, x.size(), x, y, out);
}

inline void runTogether(Binary op, Side side,
                        ColorList const& x, ColorList const& y,
                        ColorList& out) {
    auto size = std::min(x.size(), y.size());
    out.resize(size);
    detail::run(side, op, size, x, y, out);
}

} // operation
} // tdsp
