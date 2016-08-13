#pragma once

#include <array>
#include <utility>
#include <vector>

#include <timedata/base/className.h>
#include <timedata/base/enum.h>
#include <timedata/signal/ranged.h>

namespace timedata {

template <typename Sample, typename Function>
Sample& applyInto(Sample& out, Function f) {
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = f(out[i]);
    return out;
}

template <typename Sample, typename Function>
Sample applyNew(Sample const& in, Function f) {
    Sample out;
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = f(in[i]);
    return out;
}

template <typename Sample, typename Function>
Sample& applyInto(Sample const& in, Sample& out, Function f) {
    for (size_t i = 0; i < out.size(); ++i)
        out[i] = f(out[i], in[i]);
    return out;
}

template <typename Model, typename Range>
using SampleBase = std::array<Ranged<Range>, enumSize<Model>()>;

template <typename Model, typename Range = Normal<float>>
struct Sample : SampleBase<Model, Range> {
    using base_type = SampleBase<Model, Range>;
    using model_type = Model;
    using range_type = Range;
    using sample_type = Sample;

    using value_type = ValueType<base_type>;
    using number_type = ValueType<value_type>;

    using is_container = std::false_type;

    using FunctionPointer = number_type (*)(number_type);

    using base_type::base_type;
    using base_type::operator[];

    static const auto SIZE = enumSize<Model>();

    using ListBase = std::vector<Sample>;
    struct List : ListBase {
        using ListBase::ListBase;

        using model_type = Model;
        using number_type = typename Sample::number_type;
        using range_type = Range;
        using ranged_type = typename Sample::value_type;
        using sample_type = Sample;
        using value_type = Sample;

        using is_container = std::true_type;
    };

    // TODO: need to use std::initializer_list!
    Sample(value_type r, value_type g, value_type b)
            : base_type{{r, g, b}} {
    }

    Sample() {
        clear();
    }

    void clear() {
        base_type::fill({});
    }

    Sample forEachF(FunctionPointer fp) const {
        return applyNew(*this, fp);
    }

    Sample scale() const {
        return applyNew(*this, &timedata::scale<Range>);
    }

    Sample unscale() const {
        return applyNew(*this, &timedata::unscale<Range>);
    }

    static Sample infinity() {
        auto inf = value_type::infinity();
        return {inf, inf, inf};
    }

    value_type const& operator[](Model m) const {
        return base_type::at(static_cast<size_t>(m));
    }

    value_type& operator[](Model m) {
        return base_type::at(static_cast<size_t>(m));
    }

    number_type cmp(Sample const& x) const {
        for (size_t i = 0; i < SIZE; ++i)
            if (auto d = (*this)[i] - x[i])
                return d;
        return {};
    }

    bool operator==(Sample const& s) const { return cmp(s) == 0; }
    bool operator!=(Sample const& s) const { return cmp(s) != 0; }
    bool operator<(Sample const& s) const { return cmp(s) < 0; }
    bool operator<=(Sample const& s) const { return cmp(s) <= 0; }
    bool operator>(Sample const& s) const { return cmp(s) > 0; }
    bool operator>=(Sample const& s) const { return cmp(s) >= 0; }
};

template <typename T> using NumberType = typename T::number_type;
template <typename T> using RangedType = typename T::ranged_type;
template <typename T> using SampleType = typename T::sample_type;


template <typename T>
size_t getSizeof(T const& t, std::true_type) {
    return sizeof(t) + sizeof(t[0]) * t.size();
}

template <typename T>
size_t getSizeof(T const& t, std::false_type) {
    return sizeof(t);
}

template <typename Sample>
size_t getSizeof(Sample const& sample) {
    return getSizeof(sample, typename Sample::is_container());
}

}  // timedata
