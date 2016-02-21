#pragma once

#include <limits>
#include <fcolor/color/color.h>

namespace fcolor {

template <typename Number>
struct Packer {
    using Pack = uint64_t;
};

template <>
struct Packer<uint8_t> {
    using Pack = uint32_t;
};

template <typename Number>
using Pack = typename Packer<Number>::Pack;

template <typename Number, typename Alpha = void>
Pack<Number> pack(Color<Number, Alpha> const&);

template <typename Number>
Color<Number> unpack(Pack<Number>);

template <typename Number, typename Alpha>
Color<Number, Alpha> unpackAlpha(Pack<Number>);

}  // namespace fcolor
