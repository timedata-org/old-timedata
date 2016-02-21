#pragma once

#include <fcolor/color/pack.h>

namespace fcolor {

template <typename Number>
Pack<Number> scale() {
    auto max = std::numeric_limits<Number>::max();
    return static_cast<Pack<Number>>(max) + 1;
}

template <typename Number, typename Alpha>
Pack<Number> pack(Color<Number, Alpha> const& c) {
    auto s = scale<Number>();
    return ((c.alpha * s + c.red) * s + c.green) * s + c.blue;
}

template <typename Number>
Pack<Number> pack(Color<Number> const& c) {
    auto s = scale<Number>();
    return (c.red * s + c.green) * s + c.blue;
}

template <typename Number>
Color<Number> unpack(Pack<Number> x) {
    auto s = scale<Number>();
    auto b = static_cast<Number>(x % s);
    x /= s;
    auto g = static_cast<Number>(x % s);
    x /= s;
    auto r = static_cast<Number>(x % s);

    return {r, g, b};
}

template <typename Number, typename Alpha>
Color<Number, Alpha> unpackAlpha(Pack<Number> x) {
    auto s = scale<Number>();
    auto b = static_cast<Number>(x % s);
    x /= s;
    auto g = static_cast<Number>(x % s);
    x /= s;
    auto r = static_cast<Number>(x % s);
    x /= s;
    auto a = static_cast<Number>(x);

    return {r, g, b, a};
}

}  // namespace fcolor
