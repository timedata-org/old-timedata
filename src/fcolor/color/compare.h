#pragma once

#include <limits>
#include <fcolor/color/color.h>
#include <fcolor/base/number_inl.h>
#include <fcolor/base/level_inl.h>

namespace fcolor {

/** Returns a negative number x is if less than, 0 if equals, or positive if x
    is greater than y. */
template <typename T> int compare(T const& x, T const& y);

template <typename T> bool operator==(T const&, T const&);
template <typename T> bool operator!=(T const&, T const&);
template <typename T> bool operator<(T const&, T const&);
template <typename T> bool operator<=(T const&, T const&);
template <typename T> bool operator>(T const&, T const&);
template <typename T> bool operator>=(T const&, T const&);


}  // namespace fcolor
