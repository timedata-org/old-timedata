/**
   This code is temporarily disabled during rapid development of the color-only
   library.
*/

#pragma once

#include <tdsp/signal/strip.h>

namespace tdsp {

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

template <typename Sample>
using Component = typename Sample::component_t;

template <typename Sample, typename Combiner>
auto componentCombiner(Combiner combiner) {
    return [=] (Sample const& from, Sample& to) {
        for (auto i = 0; i < Sample::SIZE; ++i)
            combiner(from[i], to[i]);
    };
}

}  // tdsp
