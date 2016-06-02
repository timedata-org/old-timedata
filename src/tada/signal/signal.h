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

template <typename T = float>
struct Normal {
    using Number = T;

    static constexpr auto min = Number(0);
    static constexpr auto range = Number(1);
};

template <typename T = float>
struct EightBit {
    using Number = T;

    static constexpr auto min = Number(0);
    static constexpr auto range = Number(255);
};

template <typename Range>
using NumberOf = typename Range::Number;

/** Unscale a ranged number to a range of [0, 1].  Numbers out of band get
    scaled proportionately. */
template <typename Range>
NumberOf<Range> unscale(NumberOf<Range> x) {
    return (x - Range::min) / Range::range;
    /* TODO: only works for floating types! write/repurpose something for
       integral types. */
}

/** Scale a number with a range of [0, 1] to a ranged number.
    Numbers out of band get scaled proportionately. */
template <typename Range>
NumberOf<Range> scale(NumberOf<Range> y) {
    return Range::min + y * Range::range;
    // as above about integers.
}

template <typename Range>
struct Ranged {
    using Number = NumberOf<Range>;

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

/** EnumNames has just a single dependent class, Fields, a struct containing
    members named in order after the values in the enumerated type.

    For an example, see struct EnumNames<RGB>::Fields in colors/colors.h.
*/

template <typename Enum>
struct EnumNames;

/** A Model encapsulates everything about a time arts data stream except the
    encoding into memory (interleaved, parallel, other...)

    A Model is a union - two data structures in the same block of memory.

    One of them represents the data by name - red, green, blue.  The other
    represents the data by index - 0, 1, 2.

    These two data structures correspond to each other exactly (there are
    unit tests to prove it) so you can access data from the Model either by
    index or by name with no penalty either way.
*/
template <typename Enum, typename Range>
struct Model {
    // Imported types.
    using Number = typename Range::Number;
    using Fields = typename EnumNames<Enum>::template Fields<Number>;
    using Samples = std::array<Number, enumSize<Enum>()>;

    using enum_t = Enum;
    using range_t = Range;

    static_assert(sizeof(Samples) == sizeof(Fields),
                  "Names and Samples must be the same size");

    union {
        Samples sample;
        Fields field;
    };

    Model() : field{} {}
    Model(Samples const& s) : sample{s} {}
    Model(Fields const& f) : field{f} {}

    template<typename ...E>
    Model(E&&...e) : sample{{std::forward<E>(e)...}} {}
    // https://stackoverflow.com/questions/6893700
};

}  // tada
