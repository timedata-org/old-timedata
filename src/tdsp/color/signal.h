#pragma once

#include <array>
#include <string>
#include <type_traits>
#include <vector>

#include <tdsp/base/math.h>
#include <tdsp/base/enum.h>

namespace tdsp {

/** Signal models are definined by scoped enumerations.

    `size` always has to be the last entry in each one so we
    can generically get the number of elements in the enum class.
*/

template <typename T, size_t SIZE>
using Arrays = std::array<std::unique_ptr<T[]>, SIZE>;

template <typename T, size_t SIZE>
Arrays<T, SIZE> makeArrays(size_t elements) {
    Arrays<T, SIZE> result;
    for (auto& r: result)
        r = {new T[elements]};
}

template <typename Enum, typename T = float>
struct Model {
    using Name = Enum;
    using Number = T;

    static const auto SIZE = enumSize<Name>();

    using Sample = std::array<Number, SIZE>;
    using SampleRef = std::array<Number*, SIZE>;
};

template <typename Enum, typename T = float>
using Sample = typename Model<Enum, T>::Sample;


template <typename Model>
struct Striped {
    using model_t = Model;
    using Name = typename Model::Name;
    using Number = typename Model::Number;
    using Array = Number;

    static Number& get(Array* array, size_t index, Name name) {
        return array[index * Model::SIZE + enumSize(name)];
    }

    static Number get(Array const* array, size_t index, Name name) {
        return array[index * Model::SIZE + enumSize(name)];
    }
};

template <typename Model>
struct Parallel {
    using model_t = Model;
    using Name = typename Model::Name;
    using Number = typename Model::Number;
    using Array = Number*;

    static Number& get(Array* array, size_t index, Name name) {
        return array[enumSize(name)][index];
    }

    static Number get(Array const* array, size_t index, Name name) {
        return array[enumSize(name)][index];
    }
};

#if 0

template <typename Layout>
struct Strip {
    using layout_t = Layout;
    using Sample = typename Layout::Sample;

    Sample frame;
    size_t begin, end;

    template <typename Function>
    void forEach() (Function func) {
        Layout::forEach(frame, begin, end, func);
    }
};

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

}  // tdsp
