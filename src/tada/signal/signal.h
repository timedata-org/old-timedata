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
    using BaseSample = std::array<value_type, SIZE>;

    struct Sample : BaseSample {
        using BaseSample::BaseSample;

        Sample(value_type r, value_type g, value_type b)
                : BaseSample{{r, g, b}} {
        }
        Sample() {
            BaseSample::fill(0);
        }

        using names_t = Names;
        using range_t = Range;
        using value_type = Model::value_type;

        template <typename Function>
        Sample forEach(Function f) {
            Sample result;
            for (auto i = 0; i < this->size(); ++i)
                result[i] = f(*this)[i];
            return result;
        }
        Sample scale() const {
            return forEach([](value_type x) {
                return tada::scale<Range>(x);
            });
        }
        Sample unscale() const {
            return forEach([](value_type x) {
                return tada::unscale<Range>(x);
            });
        }
    };

    using Vector = std::vector<Sample>;
};

}  // tada
