#pragma once

#include <fcolor/color/color.h>

namespace fcolor {

Color<uint8_t> fromName(const std::string& cname);

std::string toName(const Color&);

}  // namespace fcolor
