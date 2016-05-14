#pragma once

#include <tdsp/color/operation.h>
#include <tdsp/color/colorList_inl.h>

namespace tdsp {
namespace detail {

using Unary = Operation::Unary;
using Binary = Operation::Binary;

template <Unary> float unary(float);

template <> inline float unary<Unary::ABS>(float x)    { return std::abs(x); }
template <> inline float unary<Unary::CLEAR>(float)    { return 0.0f; }
template <> inline float unary<Unary::INVERT>(float x) { return invert(x); }
template <> inline float unary<Unary::NEGATE>(float x) { return -x; }

template <typename Function>
void assignEach(ColorList& colors, Function f) {
    for (auto& color: colors)
        for (auto& c: color)
            c = f(c);
}

template <Binary> float binary(float x, float y);

template <> float binary<Binary::ADD>(float x, float y) { return x + y; }
template <> float binary<Binary::DIV>(float x, float y) { return x / y; }
template <> float binary<Binary::MAX>(float x, float y) { return std::max(x, y); }
template <> float binary<Binary::MIN>(float x, float y) { return std::min(x, y); }
template <> float binary<Binary::MUL>(float x, float y) { return x * y; }
template <> float binary<Binary::POW>(float x, float y) { return pow(x, y); }
template <> float binary<Binary::SUB>(float x, float y) { return x - y; }

template <Binary bin>
float reverse(float x, float y) { return binary<bin>(y, x); }

template <typename Function>
void assign(float in, ColorList& out, Function f) {
    for (auto& color: out)
        for (auto& c: color)
            c = f(in, c);
}

template <typename Function>
void assign(ColorList const& in, ColorList& out, Function f) {
    auto size = std::min(in.size(), out.size());
    for (size_t i = 0; i < size; ++i) {
        for (auto j = 0; j < 3; ++j) {
            auto& c = out[i][j];
            c = f(in[i][j], c);
        }
    }
}

template <typename Input>
void runLeft(Binary op, Input const& in, ColorList& out) {
    switch (op) {
        case Binary::ADD: return assign(in, out, binary<Binary::ADD>);
        case Binary::DIV: return assign(in, out, binary<Binary::DIV>);
        case Binary::MAX: return assign(in, out, binary<Binary::MAX>);
        case Binary::MIN: return assign(in, out, binary<Binary::MIN>);
        case Binary::MUL: return assign(in, out, binary<Binary::MUL>);
        case Binary::POW: return assign(in, out, binary<Binary::POW>);
        case Binary::SUB: return assign(in, out, binary<Binary::SUB>);
        case Binary::size: return;
    }
}

template <typename Input>
void runRight(Binary op, Input const& in, ColorList& out) {
    switch (op) {
        case Binary::ADD: return assign(in, out, reverse<Binary::ADD>);
        case Binary::DIV: return assign(in, out, reverse<Binary::DIV>);
        case Binary::MAX: return assign(in, out, reverse<Binary::MAX>);
        case Binary::MIN: return assign(in, out, reverse<Binary::MIN>);
        case Binary::MUL: return assign(in, out, reverse<Binary::MUL>);
        case Binary::POW: return assign(in, out, reverse<Binary::POW>);
        case Binary::SUB: return assign(in, out, reverse<Binary::SUB>);
        case Binary::size: return;
    }
}

inline void run(Unary op, ColorList& out) {
    switch (op) {
        case Unary::ABS:    return assignEach(out, unary<Unary::ABS>);
        case Unary::CLEAR:  return assignEach(out, unary<Unary::CLEAR>);
        case Unary::INVERT: return assignEach(out, unary<Unary::INVERT>);
        case Unary::NEGATE: return assignEach(out, unary<Unary::NEGATE>);
        case Unary::size:   return;
    }
}

} // namespace detail

void run(Operation::Unary op, ColorList& out) {
    return detail::run(op, out);
}

void runLeft(Operation::Binary op, float in, ColorList& out) {
    return detail::runLeft(op, in, out);
}

void runLeft(Operation::Binary op, ColorList const& in, ColorList& out) {
    return detail::runLeft(op, in, out);
}

void runRight(Operation::Binary op, float in, ColorList& out) {
    return detail::runRight(op, in, out);
}

void runRight(Operation::Binary op, ColorList const& in, ColorList& out) {
    return detail::runRight(op, in, out);
}

} // tdsp
