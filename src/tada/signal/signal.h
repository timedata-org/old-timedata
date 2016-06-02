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

namespace v2 {

/** FieldStruct is a struct with float fields with the same name and order as
    the values in Enum. */
template <typename Enum, typename Number>
struct FieldStruct;

template <typename Enum, typename Range>
struct Model {
    using Number = typename Range::number_t;
    using Fields = FieldStruct<Enum, Number>;
    using Sample = std::array<Number, enumSize<Enum>()>;
    using enum_t = Enum;
    using number_t = Number;
    using range_t = Range;


    struct Access {
        static_assert(sizeof(Sample) == sizeof(Names<Enum>),
                      "Names and Sample must be the same size");

        union {
            Sample sample;
            Fields fields;
        };

        Access() : fields{} {}
        Access(Sample const& s) : sample{s} {}
        Access(Fields const& f) : fields{f} {}

        template<typename ...E>
        Access(E&&...e) : sample{{std::forward<E>(e)...}} {}
        // https://stackoverflow.com/questions/6893700
    };
};

}  // v2

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
