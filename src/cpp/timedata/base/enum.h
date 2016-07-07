#pragma once

#include <array>
#include <type_traits>

namespace timedata {

template< bool B, class T = void >
using enable_if_t = typename std::enable_if<B,T>::type;

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
template <
    typename Enum,
    typename = enable_if_t<std::is_enum<Enum>::value>>
constexpr uint8_t enumSize() {
    return 1 + static_cast<uint8_t>(Enum::last);
}

/** Iterate over elements of a sized enum class. */
template <typename Enum,
          typename Functor,
          typename = enable_if_t<std::is_enum<Enum>::value>>
void forEach(Functor f) {
    for (uint8_t i = 0; i < enumSize<Enum>(); ++i)
        f(static_cast<Enum>(i));
}

}  // namespace timedata
