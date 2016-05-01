#pragma once

#include <array>
#include <type_traits>

namespace tdsp {

/** Generically get the size of an enum whose last element is `size`. */
template <typename Enum>
constexpr uint8_t enumSize() {
    return static_cast<uint8_t>(Enum::size);
}

template <typename Enum, typename Functor>
void forEach(Functor f) {
    for (uint8_t i = 0; i < enumSize<Enum>(); ++i)
        f(static_cast<Enum>(i));
}

/** An array that can be accessed by number or by Enum. */
template <typename T, typename Enum>
struct EnumArray : std::array<T, enumSize<Enum>> {
    using Parent = std::array<T, enumSize<Enum>>;

    using reference = typename Parent::reference;
    reference operator[] (Enum i) {
        return operator[](static_cast<uint8_t>(i));
    }
    reference at(Enum i) {
        return at(static_cast<uint8_t>(i));
    }

    using const_reference = typename Parent::const_reference;
    const_reference operator[] (Enum i) const {
        return operator[](static_cast<uint8_t>(i));
    }
    const_reference at(Enum i) const {
        return at(static_cast<uint8_t>(i));
    }
};

}  // namespace tdsp
