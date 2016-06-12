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

    using Number = typename Range::Number;
    using BaseArray = std::array<Number, SIZE>;

    struct Array : BaseArray {
        using BaseArray::BaseArray;

        Array(Number r, Number g, Number b) : BaseArray{{r, g, b}} {}
        Array() {
            BaseArray::fill(0);
        }

        using range_t = Range;
        using names_t = Names;
    };

    using names_t = Names;
    using range_t = Range;

    using Vector = std::vector<Array>;
};

}  // tada
