#pragma once

#include <limits>
#include <fcolor/color/color.h>
#include <fcolor/base/number_inl.h>
#include <fcolor/base/level_inl.h>

namespace fcolor {

template <typename T> bool operator==(T, T);
template <typename T> bool operator!=(T, T);
template <typename T> bool operator<(T, T);
template <typename T> bool operator<=(T, T);
template <typename T> bool operator>(T, T);
template <typename T> bool operator>=(T, T);

}  // namespace fcolor
