#pragma once

#include <array>
#include <utility>
#include <vector>

#include <tada/base/enum.h>
#include <tada/signal/ranged.h>

namespace tada {

template <typename Model, typename Range>
using SampleBase = std::array<Ranged<Range>, enumSize<Model>()>;

template <typename Model, typename Range>
struct Sample : SampleBase<Model, Range> {
    using base_t = SampleBase<Model, Range>;
    using model_t = Model;
    using range_t = Range;
    using value_type = ValueType<base_t>;
    using number_t = ValueType<value_type>;

    using normal_t = Sample<Model, NormalType<Range>>;

    using base_t::base_t;

    Sample(value_type r, value_type g, value_type b)
            : base_t{{r, g, b}} {
    }
    Sample() {
        base_t::fill(0);
    }

    template <typename Function>
    Sample forEach(Function f) const {
        Sample result;
        for (auto i = 0; i < result.size(); ++i)
            result[i] = f((*this)[i]);
        return result;
    }

    using FunctionPointer = number_t (*)(number_t);
    Sample forEachF(FunctionPointer f) const {
        return forEach(f);
    }

    Sample scale() const {
        return forEachF(tada::scale<Range>);
    }

    Sample unscale() const {
        return forEachF(tada::unscale<Range>);
    }
};

}  // tada
