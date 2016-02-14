#pragma once

namespace fcolor {

template <typename Number>
struct Traits {
    /** Float is the floating point equivalent of Number - which will be the
        same as Number if it's a float, or otherwise, a "best match". */
    using Float = Number;
};

template <typename Number>
using Float = typename Traits<Number>::Float;

template <typename Float, typename T>
Float pow(Float x, T e);

template <typename Float>
Float sqrt(Float x);

} // fcolor
