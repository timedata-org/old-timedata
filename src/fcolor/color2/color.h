#pragma once

#include <array>
#include <limits>
#include <fcolor/base/level.h>

namespace fcolor {
namespace color2 {

template <typename Model>
using Number = typename Model::number_t;

template <typename Model>
using Array = std::array<Number<Model>, Model::size>;

template <typename Model>
struct Color {
    using array_t = Array<Model>;
    using model_t = Model;
    using number_t = Number<Model>;

    Array<Model> array;
};

namespace model {
template <typename Number = float>
struct RGB {
    using number_t = Number;
    static auto const size = size_t(3);

};


template <typename Number = float>
struct HSB {
    using number_t = Number;
    static auto const size = size_t(3);
};
} // model

template <typename Number = float>
using RGB = Color<model::RGB<Number>>;


template <typename Color>
struct Red {
    static Number<Color>& get(Color&);
};

template <typename Number>
struct Red<RGB<Number>> {
    static Number& get(RGB<Number>& rgb) { return rgb.array[0]; }
};

template <template<class> class Getter, typename Color>
Number<Color> get(Color& color) {
    return Getter<Color>::get(color);
}

/*
template <typename C> Number<C> red(C const&);
template <typename C> Number<C> green(C const&);
template <typename C> Number<C> blue(C const&);

template <typename C> Number<C> hue(C const&);
template <typename C> Number<C> saturation(C const&);
template <typename C> Number<C> brilliance(C const&);


template <typename T> T red(Color<RGB<T>> const& c) { return c[0]; }
template <typename T> T green(Color<RGB<T>> const& c) { return c[1]; }
template <typename T> T blue(Color<RGB<T>> const& c) { return c[2]; }

template <typename T> T& red(Color<RGB<T>>& c) { return c[0]; }
template <typename T> T& green(Color<RGB<T>>& c) { return c[1]; }
template <typename T> T& blue(Color<RGB<T>>& c) { return c[2]; }

*/

}  // color2
}  // fcolor
