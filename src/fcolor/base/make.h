#pragma once

namespace fcolor {

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

}  // fcolor
