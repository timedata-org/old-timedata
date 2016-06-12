#pragma once

#include <array>
#include <utility>
#include <vector>

#include <tada/base/enum.h>
#include <tada/signal/range.h>

namespace tada {

/** A Model encapsulates everything about a time arts signal except the
    encoding into memory (interleaved, parallel, other...)

    A Model is a union of two data structures named Fields and Samples
    in the same block of memory.

    Fields accesses the data by name - e.g. red, green, blue, while Samples
    accesses it by index - 0, 1, 2.

    These two data structures correspond to each other exactly (there are
    unit tests to prove it) so you can access data from the Model either by
    index or by name with no penalty either way.

    Fields comes from EnumFields, so a specialization of EnumFields for your
    Name and Number needs to be available to use a Model.
*/
template <typename Names, typename Range>
struct Model {
    static const auto SIZE = enumSize<Names>();

    using Number = typename Range::Number;
    using Array = std::array<Number, SIZE>;

    using names_t = Names;
    using range_t = Range;

    using Vector = std::vector<Array>;
};

}  // tada
