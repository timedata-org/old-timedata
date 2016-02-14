#pragma once

#include <fcolor/color/color.h>

namespace fcolor {
namespace color {

template <typename Color>
bool fromString(const std::string& cname, Color&);

template <typename Color>
std::string toString(const FColor&);

}  // namespace color
}  // namespace fcolor
