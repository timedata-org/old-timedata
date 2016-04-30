#pragma once

#include <array>
#include <type_traits>

namespace fcolor {

/** Cast an enum into an integer. */
template <typename Enum,
          typename std::enable_if_t<std::is_enum<Enum>::value, int> = 0>
constexpr uint8_t toUint8(Enum element) {
    return static_cast<uint8_t>(element);
}

/** Generically get the size of an enum whose last element is `size`. */
template <typename Enum,
          typename std::enable_if_t<std::is_enum<Enum>::value, int> = 0>
constexpr uint8_t enumSize() {
    return toUint8(Enum::size);
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

    using reference = Parent::reference;
    using reference operator[](size_t);
    using reference at(size_t);

    reference operator[] (Enum i) { return operator[](toUint8(i)); }
    reference at(Enum i)          { return at(toUint8(i)); }

    using const_reference = Parent::const_reference;
    using const_reference operator[](size_t);
    using const_reference at(size_t);

    const_reference operator[] (Enum i) const { return operator[](toUint8(i)); }
    const_reference at(Enum i) const          { return at(toUint8(i)); }
};

}  // namespace fcolor
