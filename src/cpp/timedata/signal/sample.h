#pragma once

#include <array>
#include <utility>
#include <vector>

#include <timedata/base/enum.h>
#include <timedata/signal/ranged.h>
#include <timedata/signal/sampleFunctions.h>

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

        struct Index {
            using model_type = Model;
            using range_type = Range;
            using sample_type = Sample;

            using value_type = ValueType<base_type>;
            using number_type = ValueType<value_type>;

            using is_container = std::false_type;

            List& list;
            size_t index;

            size_t size() const { return SIZE; }

            value_type operator[](size_t i) const {
                return index < list.size() ? list[index][i] : value_type{};
            }
        };
    };

    // TODO: need to use std::initializer_list!
    Sample(value_type r, value_type g, value_type b)
            : base_type{{r, g, b}} {
    }

    Sample() {
        base_type::fill({});
    }

    value_type const& operator[](Model m) const {
        return base_type::operator[](static_cast<size_t>(m));
    }

    value_type& operator[](Model m) {
        return base_type::operator[](static_cast<size_t>(m));
    }

    bool operator==(Sample const& s) const { return cmp(s) == 0; }
    bool operator!=(Sample const& s) const { return cmp(s) != 0; }
    bool operator<(Sample const& s) const { return cmp(s) < 0; }
    bool operator<=(Sample const& s) const { return cmp(s) <= 0; }
    bool operator>(Sample const& s) const { return cmp(s) > 0; }
    bool operator>=(Sample const& s) const { return cmp(s) >= 0; }

  private:
    number_type cmp(Sample const& x) const {
        return compareTo(*this, x);
    }
};

// TODO: need a better place for this.
using CIndexList = std::vector<int>;

template <typename Container>
size_t getSizeof(Container const& t, std::true_type) {
    return sizeof(t) + sizeof(t[0]) * t.size();
}

template <typename Sample>
size_t getSizeof(Sample const& t, std::false_type) {
    return sizeof(t);
}

template <typename Item>
size_t getSizeof(Item const& x);

template <typename Item>
size_t getSizeof(Item const& x) {
    return getSizeof(x, typename Item::is_container());
}

template <>
inline size_t getSizeof(CIndexList const& x) {
    return getSizeof(x, std::true_type());
}

}  // timedata
