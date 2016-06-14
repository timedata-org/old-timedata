#pragma once

namespace tada {

template <typename T = float>
struct Normal {
    using value_type = T;

    static constexpr auto start = value_type(0);
    static constexpr auto range = value_type(1);
};

template <typename T = float>
struct EightBit {
    using value_type = T;

    static constexpr auto start = value_type(0);
    static constexpr auto range = value_type(255);
};

template <typename Range>
using ValueType = typename Range::value_type;

/** Unscale a ranged number to a range of [0, 1].  Numbers out of band get
    scaled proportionately. */
template <typename Range>
ValueType<Range> unscale(ValueType<Range> x) {
    return (x - Range::start) / Range::range;
}

/** Scale a number with a range of [0, 1] to a ranged number.
    Numbers out of band get scaled proportionately. */
template <typename Range>
ValueType<Range> scale(ValueType<Range> y) {
    return Range::start + y * Range::range;
}

/* TODO: above two functions only work for floating types! write/repurpose
   something for integral types. */

template <typename Range>
ValueType<Range> invert(ValueType<Range> y) {
    if (Range::start < 0)
        return -y;
    // TODO: what if start > 0?  Why would this be?
    return y > 0 ? Range::range - y : -(Range::range + y);
}

}  // tada
