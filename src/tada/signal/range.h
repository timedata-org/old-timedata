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
    static constexpr auto range = value_type(256);
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

/** A Ranged number looks like an underlying numeric type, but with a
    generically attached Range.

    "Generic" means that there is no cost at run-time to carrying this
    information around - the downside is that we have to instantiate a new
    template for each range we want, but since the total number is very small,
    this is almost free. */
template <typename Range>
struct Ranged {
    using value_type = ValueType<Range>;

    value_type value;

    Ranged() = default;
    Ranged(Ranged const&) = default;
    Ranged(value_type n) : value(n) {}

    value_type unscale() const {
        return tada::unscale<Range>(value);
    }

    static Ranged scale(value_type v) {
        return tada::scale<Range>(v);
    }

    template <typename Range2>
    operator Ranged<Range2>() const {
        return tada::scale<Range2>(tada::unscale<Range>(value));
    }

    operator value_type() const { return value; }
    operator value_type&() { return value; }
};

}  // tada
