#pragma once

#include <array>
#include <string>
#include <type_traits>
#include <vector>

#include <tada/base/math.h>
#include <tada/base/enum.h>

namespace tada {

/** Signal models are definined by sized scoped enumerations
*/

template <typename Enum, typename Number = float>
struct Model {
    using enum_t = Enum;
    using number_t = Number;

    /** Names is a struct with float fields with the same name and order
        as the values in Enum! */
    struct Names;

    static const auto SIZE = enumSize<Enum>();
    using Sample = std::array<Number, SIZE>;
};

template <typename Enum, typename Number = float>
using Sample = typename Model<Enum, Number>::Sample;

template <typename Enum, typename Number = float>
using Names = typename Model<Enum, Number>::Names;

template <typename Number = float>
struct Normal {
    using number_t = Number;

    static constexpr auto min = Number(0);
    static constexpr auto range = Number(1);
};

template <typename Number = float>
struct EightBit {
    using number_t = Number;

    static constexpr auto min = Number(0);
    static constexpr auto range = Number(255);
};

template <typename Range>
using Number = typename Range::number_t;

/* TODO: only works for floating types! write/repurpose something for
   integral types. */

/** Unscale a ranged number to a range of [0, 1].  Numbers out of band get
    scaled proportionately. */
template <typename Range>
Number<Range> unscale(Number<Range> x) {
    return (x - Range::min) / Range::range;
}

/** Scale a number with a range of [0, 1] to a ranged number.
    Numbers out of band get scaled proportionately. */
template <typename Range>
Number<Range> scale(Number<Range> y) {
    return Range::min + y * Range::range;
}

template <typename Range>
struct Ranged {
    using Number = typename Range::number_t;

    Number number;

    Ranged() = default;
    Ranged(Ranged const&) = default;

    Ranged(Number n) : number(n) {}

    template <typename Range2>
    operator Ranged<Range2>() const {
        return scale<Range2>(unscale<Range>(number));
    }

    operator Number() const { return number; }
    operator Number&() { return number; }
};

#if 0
namespace three {
// New version with three templates as per the document.

template <typename Enum, typename Range>
struct Model {
    static const auto SIZE = enumSize<Enum>();

    using enum_t = Enum;
    using range_t = Range;

    using number_t = typename Range::number_t;

    /** One sample of time data. */
    using Sample = std::array<number_t, SIZE>;

    /** Names is a struct with float fields with the same name and order
        as the values in Enum! */
    struct Names;

    /** Access is a union of a Name and a Sample. */
    struct Access;
};


template <typename RangeFrom, typename RangeTo>
RangeTo convert(RangeFrom x) {


    /* TODO: only works for floating types! write/repurpose something for
       integral types. */
}


template <typename Enum, typename Range>
struct Access {
    static_assert(sizeof(Sample<Enum, Number>) == sizeof(Names<Enum, Number>),
                  "Names and Sample must be the same size");

    union {
        Sample<Enum, Number> sample;
        Names<Enum, Number> names;
    };

    Access() : names{} {}

    template<typename ...E>
    Access(E&&...e) : sample{{std::forward<E>(e)...}} {}
    // https://stackoverflow.com/questions/6893700
};


}  // three

#endif

template <typename Enum, typename Number = float>
struct Access {
    static_assert(sizeof(Sample<Enum, Number>) == sizeof(Names<Enum, Number>),
                  "Names and Sample must be the same size");

    union {
        Sample<Enum, Number> sample;
        Names<Enum, Number> names;
    };

    Access() : names{} {}

    template<typename ...E>
    Access(E&&...e) : sample{{std::forward<E>(e)...}} {}
    // https://stackoverflow.com/questions/6893700
};

}  // tada
