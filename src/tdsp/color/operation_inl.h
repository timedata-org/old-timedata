#pragma once

#include <limits>

#include <tdsp/color/operation.h>
#include <tdsp/color/colorList_inl.h>

namespace tdsp {
namespace operation {
namespace detail {

/*
 Unary functions.
*/

template <Unary> float run(float);

template <> float run<Unary::ABS>(float x)    { return std::abs(x); }
template <> float run<Unary::CLEAR>(float)    { return 0.0f; }
template <> float run<Unary::INVERT>(float x) { return invert(x); }
template <> float run<Unary::NEGATE>(float x) { return -x; }

template <typename Function>
void assignEach(ColorList& colors, Function f) {
    for (auto& color: colors)
        for (auto& c: color)
            c = f(c);
}

inline void run(Unary op, ColorList& out) {
    switch (op) {
        case Unary::ABS:    return assignEach(out, run<Unary::ABS>);
        case Unary::CLEAR:  return assignEach(out, run<Unary::CLEAR>);
        case Unary::INVERT: return assignEach(out, run<Unary::INVERT>);
        case Unary::NEGATE: return assignEach(out, run<Unary::NEGATE>);
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

inline size_t listSize(float) {
    return std::numeric_limits<size_t>::max();
}

inline size_t listSize(ColorList const& cl) {
    return cl.size();
}

inline float get(float x, size_t, size_t) {
    return x;
}

inline float get(ColorList const& x, size_t i, size_t j) {
    return x[i][j];
}

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

inline
void run(Unary op, ColorList& out) {
    return detail::run(op, out);
}

template <typename Y>
void run(Binary op, Side side, Y const& y, ColorList& out) {
    auto size = std::min(out.size(), y.size());
    detail::run(side, op, size, out, y, out);
}

template <typename X, typename Y>
void run(Binary op, Side side, X const& x, Y const& y, ColorList& out) {
    auto size = std::min(x.size(), y.size());
    out.resize(size);
    detail::run(side, op, size, x, y, out);
}

} // operation
} // tdsp
