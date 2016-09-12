#pragma once

#include <cstddef>

namespace timedata {

template <typename T> using NumberType = typename T::number_type;
template <typename T> using RangedType = typename T::ranged_type;
template <typename T> using SampleType = typename T::sample_type;

template <typename Sample, typename Function>
Sample& applyInto(Sample& out, Function f) {
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = f(out[i]);
    return out;
}

template <typename Sample, typename Function>
Sample& applyInto(Sample const& in, Sample& out, Function f) {
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = f(out[i], in[i]);
    return out;
}

template <typename Sample, typename Function>
Sample applyNew(Sample const& in, Function f) {
    Sample out;
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = f(in[i]);
    return out;
}

template <typename Sample>
Sample applyNewFunction(Sample const& in, typename Sample::FunctionPointer f) {
    return applyNew(in, f);
}

template <typename Sample>
NumberType<Sample> compareTo(Sample const& x, Sample const& y) {
    for (size_t i = 0; i < x.size(); ++i)
        if (auto d = x[i] - y[i])
            return d;
    return {};
}

} // timedata
