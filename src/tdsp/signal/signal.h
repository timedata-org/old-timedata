#pragma once

#include <array>
#include <string>
#include <type_traits>
#include <vector>

#include <tdsp/base/math.h>
#include <tdsp/base/enum.h>

namespace tdsp {

/** Signal models are definined by sized scoped enumerations
*/

template <typename Enum, typename T = float>
struct Model {
    using Name = Enum;
    using Number = T;

    static const auto SIZE = enumSize<Name>();

    using Sample = std::array<Number, SIZE>;
    using SampleRef = std::array<Number*, SIZE>;
};

template <typename Enum, typename T = float>
using Sample = typename Model<Enum, T>::Sample;

}  // tdsp
