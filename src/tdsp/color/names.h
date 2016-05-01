#pragma once

#include <tdsp/color/color.h>
#include <tdsp/base/stl.h>

namespace tdsp {
namespace name {

using ToValue = std::map<std::string, uint32_t>;
using FromValue = std::map<uint32_t, std::string>;
using ToColor = std::map<std::string, Color8>;

ToValue const& toValue();
FromValue const& fromValue();
ToColor const& toColor();

} // name
} // tdsp
