#pragma once

#include <array>
#include <utility>
#include <vector>

#include <tada/base/enum.h>
#include <tada/signal/range.h>

namespace tada {

/** A Model encapsulates everything about a time arts signal except the
    encoding into memory (interleaved, parallel, other...)
*/
template <typename Names, typename Range>
struct Model {
    static const auto SIZE = enumSize<Names>();

    using value_type = typename Range::value_type;
    using BaseArray = std::array<value_type, SIZE>;

    struct Array : BaseArray {
        using BaseArray::BaseArray;

        Array(value_type r, value_type g, value_type b) : BaseArray{{r, g, b}} {}
        Array() {
            BaseArray::fill(0);
        }

        using names_t = Names;
        using range_t = Range;
        using value_type = Model::value_type;
    };

    using Vector = std::vector<Array>;
};

}  // tada
