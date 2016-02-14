#pragma once

#include <utility>

namespace fcolor {

template <typename Number>
struct Traits {
    /** Float is the floating point equivalent of Number - which will be the
        same as Number if it's a float, or otherwise, a "best match". */
    using Float = Number;
};

template <typename Number>
using Float = typename Traits<Number>::Float;

template <typename Number>
using Pair = std::pair<Number, Number>;

template <typename Float>
Pair<Float> modf(Float);

template <typename Float = double>
Float pi();

} // fcolor
