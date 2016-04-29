#pragma once

#include <array>
#include <string>
#include <vector>

#include <fcolor/base/Math.h>

namespace fcolor3 {

using namespace fcolor;

/** Color models are definined by scoped enumerations.
    `size` always has to be the last entry in each one so we
    can generically get the number of elements in the enum class. */
enum class RGB { red, green, blue, size };
enum class RGBW { red, green, blue, white, size };
enum class HSB { hue, saturation, brightness, size };
// etc.

template <typename Names, typename Component = float>
struct Color {
    using component_t = Component;
    using names_t = Names;
    static auto const SIZE = enumSize<Names>();

    using Components = std::array<Component, enumSize<Names>()>;
    Components components;

    struct List {
        std::vector<Component> components;

        explicit List(size_t size) : components(SIZE * size) {}

        size_t size() const { return components.size() / SIZE; }

        // DANGEROUS old style C casts - but no other neat way to do it?
        Color*       begin()       { return (Color*)(&components[0]); }
        Color const* begin() const { return (Color const*)(&components[0]); }
        Color*       end()         { return begin() + size(); }
        Color const* end() const   { return begin() + size(); }

        Color&       operator[](size_t i)       { return begin()[i]; }
        Color const& operator[](size_t i) const { return begin()[i]; }
    };
};

template <typename Color>
using Component = typename Color::component_t;

template <typename Color, typename Combiner>
auto componentCombiner(Combiner combiner) {
    return [=] (Color const& from, Color& to) {
        for (auto i = 0; i < Color::SIZE; ++i)
            combiner(from[i], to[i]);
    };
}

struct Mask {
    // A bit flag - is a color component muted?
    int mute;

    // A bit flag - is a color component inverted?
    int invert;

    float brightness;

    template <typename Color, typename Combiner>
    void operator()(Color const& from, Color& to, Combiner const& comb) const {
        auto mute = this->mute, invert = this->invert;
        for (auto i = 0; i < Color::SIZE; ++i) {
            if (shift(mute))
                continue;
            auto c = from[i];
            if (shift(invert))
                c = 1.0f - c;
            comb(c * brightness, to[i]);
        }
    }
};

}  // fcolor
