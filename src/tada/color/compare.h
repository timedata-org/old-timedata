#pragma once

#include <limits>
#include <tada/color/color.h>
#include <tada/base/number_inl.h>
#include <tada/base/level_inl.h>

namespace tada {

template <typename T> bool operator==(T, T);
template <typename T> bool operator!=(T, T);
template <typename T> bool operator<(T, T);
template <typename T> bool operator<=(T, T);
template <typename T> bool operator>(T, T);
template <typename T> bool operator>=(T, T);

}  // namespace tada
