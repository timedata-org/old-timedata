#pragma once

#include <timedata/base/math.h>

namespace timedata {

template <typename T = float>
struct Normal {
    using value_type = T;

    static constexpr auto START = value_type(0);
    static constexpr auto RANGE = value_type(1);
};

template <typename T = float>
struct EightBit {
    using value_type = T;

    static constexpr auto START = value_type(0);
    static constexpr auto RANGE = value_type(256);
};

template <typename T = float>
struct Range255 {
    using value_type = T;

    static constexpr auto START = value_type(0);
    static constexpr auto RANGE = value_type(255);
};

template <typename T>
using ValueType = typename T::value_type;

template <typename Range>
using NormalType = Normal<ValueType<Range>>;

/** Unscale a ranged number to a range of [0, 1].  Numbers out of band get
    scaled proportionately. */
template <typename Range>
ValueType<Range> unscale(ValueType<Range> x) {
    return (x - Range::START) / Range::RANGE;
}

/** Scale a number with a range of [0, 1] to a ranged number.
    Numbers out of band get scaled proportionately. */
template <typename Range>
ValueType<Range> scale(ValueType<Range> y) {
    return Range::START + y * Range::RANGE;
}

}  // timedata
