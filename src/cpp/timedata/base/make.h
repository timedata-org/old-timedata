#pragma once

#include <cstddef>
#include <memory>

namespace timedata {

template <template <typename X> class Class, typename X>
Class<X> make(X x) {
    return {x};
}

template <template <typename X> class Class, typename X, class Y>
Class<X> make(X x, Y y) {
    return {x, y};
}

template <template <typename X> class Class, typename X, class Y, class Z>
Class<X> make(X x, Y y, Z z) {
    return {x, y, z};
}

template <template <typename X, typename Y> class Class, typename X, class Y>
Class<X, Y> make2(X x, Y y) {
    return {x, y};
}

template <template <typename X, typename Y> class Class,
          typename X, class Y, class Z>
Class<X, Y> make2(X x, Y y, Z z) {
    return {x, y, z};
}

// Not yet used.
template <typename T, size_t SIZE>
using Arrays = std::array<std::unique_ptr<T[]>, SIZE>;

template <typename T, size_t SIZE>
Arrays<T, SIZE> makeArrays(size_t elements) {
    Arrays<T, SIZE> result;
    for (auto& r: result)
        r = {new T[elements]};
}

}  // timedata
