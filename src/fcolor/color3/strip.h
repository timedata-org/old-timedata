#pragma once

#include <math.h>
#include <string>
#include <fcolor/color3/color.h>

namespace fcolor3 {

// Anticpate a "Ranges".
template <typename Collection, typename Functor>
void forEach(Collection& c, Functor f) {
    std::for_each(c.begin(), c.end(), f);
}

/** Represent a "strip" of Colors contained inside a longer list or array. */
template <typename Color>
class Strip {
  public:
    using color_t = Color;

    Strip(Color& b, size_t s)             : base_(b), size_(s) {}
    Strip(typename Color::List& cl)       : base_(cl[0]), size_(cl.size()) {}
    Strip(typename Color::List const& cl) : base_(cl[0]), size_(cl.size()) {}

    size_t size() const { return size_; }

    Color* begin() const { return &base_; }
    Color* end() const { return begin() + size_; }

    auto beginComponent() const { return &(begin()[0][0]); }
    auto endComponent() const { return &(end()[0][color_t::SIZE]); }
    /** TODO: there's a rule that says I can reference that location beyond the
        end in that fashion - find out what it is. */

    Color& operator[](size_t i) const { return begin()[i]; }

    /** Checked version. */
    Color& at(size_t i) const {
        if (i >= 0 && i < size_)
            return (*this)[i];
        throw std::runtime_error("Bad index " + std::to_string(i));
    }

    operator Strip<Color const>() { return {base_, size_}; }

    /** A struct to access a strip by components.  Example code:

            auto component = strip.components()[17]; // Get the 17th component.
            strip.components()[17] = strip.components()[12];  // Copy it!

        or

            for (auto& components: strip.components()) {

    */
    struct Components {
        Strip& parent;

        auto begin() const { return parent.beginComponent(); }
        auto end() const { return parent.endComponent(); }
        auto size() const { return end() - begin(); }

        auto& operator[](size_t i) const { return begin()[i]; }
    };

    Components components() const {
        return {*this};
    }

  private:
    Color& base_;
    size_t size_;
};

template <typename X, typename Y, typename Functor>
void forEachPair(X x, Y y, Functor functor) {
    for (size_t i = 0; i < std::min(x.size(), y.size()); ++i)
        functor(x[i], y[i]);
}

template <typename Color>
Strip<Color> strip(Color& base, size_t size) {
    return {base, size};
}

template <typename Color>
Strip<Color> strip(typename Color::List& colorList) {
    return {colorList[0], colorList.size() };
}

template <typename Color>
Strip<Color const> strip(typename Color::List const& colorList) {
    return {colorList[0], colorList.size() };
}

struct SubStrip {
    int offset;
    int phase;

    template <typename Color, typename Combiner>
    void operator()(Strip<Color const> from, Strip<Color> to, Combiner comb) {
        auto fromSize = from.size(),
            toSize = to.size(),
            begin = std::min(std::max(0, offset), toSize),
            end = std::max(begin, std::min(offset + int(from.size), toSize)),
            size = end - begin;

        for (size_t i = 0, p = begin + mod(-phase, size); i < size; ++i, ++p) {
            if (p >= end)
                p -= size;
            comb(from.at(p), to.at(i));
        }
    }
};

template <typename Number>
struct Limiter {
    Number min;
    Number max;

    void operator()(Number& x) const {
        x = std::max(min, std::min(max, x));
    }
};

inline
auto gammaMaker(float& gamma) {
    return [&] (float& x) { x = powf(x, gamma); };
}

inline
auto brightnessMaker(float& brightness) {
    return [&] (float& x) { x *= brightness; };
}

template <typename F1, typename F2>
auto composer(F1 f1, F2 f2) {
    return [&] (float& x) { f1(x); f2(x); };
}

template <typename From, typename To>
void staticCaster(From from, To& to) {
    to = static_cast<To>(from);
}

template <typename Color>
void limitStrip(Strip<Color> strip, Component<Color> max,
                Component<Color> min = 0) {
    forEach(strip.components(), Limiter<Color>{min, max});
}

template <typename Color1, typename Color2>
void copyTo(Strip<Color1 const> from, Strip<Color2> to) {
    static_assert(Color1::SIZE == Color2::SIZE, "color sizes differ");
    using C1 = Component<Color1>;
    using C2 = Component<Color2>;
    forEachPair(from.components(), to.Components(), staticCaster<C1, C2>);
}

template <typename Color>
void gammaBrightness(Strip<Color> strip, float brightness, float gamma) {
    for (auto& c: strip.components)
        c = powf(c * brightness, gamma);
}

}  // fcolor
