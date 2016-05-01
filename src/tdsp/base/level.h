#pragma once

#include <tdsp/base/number.h>

namespace tdsp {
namespace level {

/** We're defining the ranges of numbers used to represent *levels* -
    components of colors.

    Color levels differ from audio or electronic signals because they can't be
    negative!

    This is all done generically - so we can use any C++ numeric type.
      * Floating point numbers range from 0 to 1.
      * Integers range from zero to the maximum possible integer of that type.

    Values beyond these ranges are never an error and are always limited to
    within the valid range in the final output.  Of course, if you're doing
    integer arithmetic you need to be careful not to trash your results with
    integer over- or underflow.
*/

/** maximum<Number>() is the maximum level for that type - representing "all of
    this color" or "100% alpha".

    Do note that, if Number is an integer type, the expression 1 +
    maximum<Number>() will silently overflow and, most likely, lead to problems.
*/
template <typename Number>
Number maximum();

/** Convert between two types of level. */
template <typename To, typename From>
To convert(From);

/** Limit a level to be within range.

    This might only be called at the very final step for floating point - it
    might be desirable to allow out-of-range numbers in intermediate results. */
template <typename Number>
Number limit(Number);

/** Convert a level of any type to the "best" floating point representation. */
template <typename Number>
Float<Number> toFloat(Number);

template <typename Number, typename Float>
Number interpolate(Number begin, Number end, Float ratio);

/** This can be a variable interpolator if Float is std::shared_ptr! */
template <typename Number, typename Float>
auto interpolator(Float ratio) {
    return [=] (Number begin, Number end) {
        auto b = Float(begin), e = Float(end);
        return Number(b + ratio * (e - b));
    };
}

} // level
} // tdsp
