#pragma once

#include <limits>
#include <tdsp/color/color.h>
#include <tdsp/base/number_inl.h>
#include <tdsp/base/level_inl.h>

namespace tdsp {

template <typename T> bool operator==(T, T);
template <typename T> bool operator!=(T, T);
template <typename T> bool operator<(T, T);
template <typename T> bool operator<=(T, T);
template <typename T> bool operator>(T, T);
template <typename T> bool operator>=(T, T);

}  // namespace tdsp
