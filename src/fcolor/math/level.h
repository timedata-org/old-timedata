#pragma once

#include <fcolor/math/float.h>

namespace fcolor {

/** We're defining the ranges of numbers used to represent *levels* -
    components of colors.

    Color levels differ from audio or electronic signals because they can't be
    negative!

    This is all done generically - so we can use any C++ type.

    Floating point numbers range from 0 to 1.
    Integers range from zero to the maximum possible integer of that type.

    Values beyond these ranges are never an error and are always limited to
    within the valid range in the final output.
*/
template <typename Number>
Number maximum();

/** Convert between two types of range. */
template <typename To, typename From>
To convert(From);

/** Limit a number to be within range.
    This should only be called at the very final step for floating point - it
    might be desirable to allow out-of-range numbers in intermediate results.

    ints must of course be limited in some way at each step. */
template <typename Number>
Number limit(Number);

template <typename Number>
Float<Number> toFloat(Number);

} // fcolor
