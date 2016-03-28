#pragma once

#include <array>
#include <fcolor/base/base.h>

namespace fcolor {

template <size_t index, typename T, size_t size>
struct Getter {
    static_assert(index < size, "Index out of range");

    using array_t = std::array<T, size>;
    using type_t = T;

    static T get(array_t const& a) { return a[index]; }
    static T& get(array_t& a) { return a[index]; }
};

template <size_t index, typename T, size_t size>
T getter(std::array<T, size> const& a) {
    return Getter<index, T, size>::get(a);
}

template <size_t index, typename T, size_t size>
T& getter(std::array<T, size>& a) {
    return Getter<index, T, size>::get(a);
}

} //fcolor
