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
