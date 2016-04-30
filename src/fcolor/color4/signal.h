#pragma once

#include <array>
#include <string>
#include <vector>

#include <fcolor/base/Math.h>
#include <fcolor/base/enum.h>

namespace fcolor4 {

/** Signal models are definined by scoped enumerations.

    `size` always has to be the last entry in each one so we
    can generically get the number of elements in the enum class.
*/
enum class RGB { red, green, blue, size };
enum class RGBW { red, green, blue, white, size };
enum class HSB { hue, saturation, brightness, size };
enum class Stereo { left, right };
// etc.

using namespace fcolor;

template <typename Name, typename Number>
struct Traits {
    static const auto SIZE = enumSize<Name>();

    using name_t = Name;
    using number_t = Number;

    using Frame = std::array<Number, SIZE>;
    using FramePointer = std::array<Number*, SIZE>;
};

template <typename Traits>
struct Striped {
    static Number& get(FramePointer frame, size_t index, Name name) {
        return frame[index * SIZE + enumSize(name)];
    }

    template <typename Function>
    static void forEach(Frame frame, size_t begin, size_t end, Function func) {
        while (auto i = begin; i < end; ++i) {
            for (auto j = 0; j < SIZE; ++j, ++frame)
                f(*frame, i, j);
        }
    }

    template <typename Function>
    static void forEachFrame(Frame frame, size_t b, size_t e, Function f) {
        forEach(frame, b, e, f);
    }
};

template <typename Name, typename Number>
struct Parallel {
    static const auto SIZE = enumSize<Name>();

    using Frame = std::array<Number*, SIZE>;
    using name_t = Name;
    using number_t = Number;

    static Number& get(Frame const& frame, size_t frameNumber, Name name) {
        return frame[enumSize(name)][frameNumber];
    }

    template <typename Function>
    static void forEach(Frame frame, size_t begin, size_t end, Function f) {
        for (auto n = 0; n < SIZE; ++n) {
            auto fr = frame[n];
            while (auto i = begin; i < end; ++i)
                f(fr[i], i, static_cast<Name>(n));
        }
    }

    template <typename Function>
    static void forEachFrame(Frame frame, size_t begin, size_t end, Function f) {
        while (auto i = begin; i < end; ++i) {
            for (auto n = 0; n < SIZE; ++n)
                f(frame[j][n], i, static_cast<Name>(n));
        }
    }
};

template <typename Layout>
struct Strip {
    using layout_t = Layout;
    using Frame = typename Layout::Frame;

    Frame frame;
    size_t begin, end;

    template <typename Function>
    void forEach() (Function func) {
        Layout::forEach(frame, begin, end, func);
    }
};

#if 0
    struct List {
        std::vector<Component> components;

        explicit List(size_t size) : components(SIZE * size) {}

        size_t size() const { return components.size() / SIZE; }

        // DANGEROUS old style C casts - but no other neat way to do it?
        Sample*       begin()       { return (Sample*)(&components[0]); }
        Sample const* begin() const { return (Sample const*)(&components[0]); }
        Sample*       end()         { return begin() + size(); }
        Sample const* end() const   { return begin() + size(); }

        Sample&       operator[](size_t i)       { return begin()[i]; }
        Sample const& operator[](size_t i) const { return begin()[i]; }
    };
};

template <typename Sample>
using Component = typename Sample::component_t;

template <typename Sample, typename Combiner>
auto componentCombiner(Combiner combiner) {
    return [=] (Sample const& from, Sample& to) {
        for (auto i = 0; i < Sample::SIZE; ++i)
            combiner(from[i], to[i]);
    };
}

struct Mask {
    // A bit flag - is a color component muted?
    int mute;

    // A bit flag - is a color component inverted?
    int invert;

    float brightness;

    template <typename Sample, typename Combiner>
    void operator()(Sample const& from, Sample& to, Combiner const& comb) const {
        auto mute = this->mute, invert = this->invert;
        for (auto i = 0; i < Sample::SIZE; ++i) {
            if (shift(mute))
                continue;
            auto c = from[i];
            if (shift(invert))
                c = 1.0f - c;
            comb(c * brightness, to[i]);
        }
    }
};
#endif

}  // fcolor
