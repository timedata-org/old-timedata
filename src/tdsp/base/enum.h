#pragma once

#include <array>
#include <type_traits>

namespace tdsp {

/** We often want to generically operate on an enum class and do things like
    "get the number of elements" or "iterate over all elements".

    There's no direct way to do this in C++, so we define an enum class to be
    "sized" if:

       1. There are no gaps.
       2. The lowest element is 0.
       3. The highest element is named `last`.

    The easiest way to do this is just to not assign numbers to any of the
    values and assign `last` to be the last value, like this:

        enum class Foo { foo, bar, baz, bang, last = bang };

*/

/** Generically get the size of a sized enum class. */
template <typename Enum>
constexpr uint8_t enumSize() {
    return 1 + static_cast<uint8_t>(Enum::last);
}

/** Iterate over elements of a sized enum class. */
template <typename Enum, typename Functor>
void forEach(Functor f) {
    for (uint8_t i = 0; i < enumSize<Enum>(); ++i)
        f(static_cast<Enum>(i));
}

/** An array indexed by a sized enum class. */
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
