#pragma once

#include <limits>
#include <timedata/color/color.h>
#include <timedata/base/number_inl.h>
#include <timedata/base/level_inl.h>

namespace timedata {

template <typename T> bool operator==(T, T);
template <typename T> bool operator!=(T, T);
template <typename T> bool operator<(T, T);
template <typename T> bool operator<=(T, T);
template <typename T> bool operator>(T, T);
template <typename T> bool operator>=(T, T);

}  // namespace timedata
