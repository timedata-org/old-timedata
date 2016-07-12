#pragma once

#include <array>
#include <utility>
#include <vector>

#include <timedata/base/className.h>
#include <timedata/base/enum.h>
#include <timedata/signal/ranged.h>

namespace timedata {

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

        size_t getSizeof() const {
            return sizeof(List) + sizeof(Sample) * this->size();
        }
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

    template <typename Function>
    Sample& into(Function f) {
        for (size_t i = 0; i < SIZE; ++i)
            (*this)[i] = f((*this)[i]);
        return (*this);
    }

    template <typename Function>
    Sample& into(Sample const& x, Function f) {
        auto& th = *this;
        for (size_t i = 0; i < SIZE; ++i)
            (*this)[i] = f((*this)[i], x[i]);
        return (*this);
    }

    Sample forEachF(FunctionPointer fp) const {
        return Sample(*this).into(fp);
    }

    Sample scale() const {
        return Sample(*this).into(&timedata::scale<Range>);
    }

    Sample unscale() const {
        return Sample(*this).into(&timedata::unscale<Range>);
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

    size_t getSizeof() const { return sizeof(Sample); }

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

}  // timedata
