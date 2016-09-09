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

/** A Sample represents a single point of time data of fixed length.  For
    example, it might be a single color pixel - or a single stereo or
    multi-channel sample - or a single DMX command.

    A Sample is generic on two types: the `Model`, and the `Range`.

    For those who aren't so well-versed in C++, "generic" means that Sample
    isn't a single class, but something like "a recipe for writing classes" -
    that you select one class for `Model`, one class for `Range` and then you
    get a new sample class named `Sample<Model, Range>`.

    The great advantage of generic programming is that the compiler knows a lot
    of things at compilation time instead of at runtime - for example, how many
    components are in a sample.  That means that a Sample has literally zero
    overhead - there is no cost at all to using a `Sample<RGB>` over using three
    variables named `r`, `g`, and `b`.  And this means we can create long lists
    of Samples and never create any new objects at all - making them extremely
    fast, but also cache coherent (TODO: better word for "laid out linearly in
    memory")

    The Model must be a C++11 enum type.  A typical Model is `RGB`.

        enum class RGB {red, green, blue};

    which corresponds to a `Sample` with three components named `red`, `green`
    and `blue`.

    One of the key properties of time data is that the numbers have "in band"
    ranges that you're expecting to see - for example, DMX values are in the
    range 0 through 255, normalized colors might be in the region 0.0 through
    1.0, and of course audio samples come in a great variety of ranges depending
    on hardware and software needs.

    But lugging around this range information for each component in each
    `Sample` would be very expensive - so we again use generic code.

    Each component of a `Sample` is a generic number called a `Ranged<Range>`.
    This contains information about the in-band, preferred range of numbers at
    compile time.


    NB: MIDI doesn't quite fit into the "sample" paradigm, because a MIDI
    message is variable length - but in practice we'd just pick a Sample size
    that's big enough for the longest non-sysex message and deal with the waste,
    which is quite acceptable since MIDI is an 7-bit control format which is
    tiny by today's standards.

 */
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
