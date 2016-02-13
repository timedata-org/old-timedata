#pragma once

#include <fcolor/Fcolor.h>

namespace fcolor {
namespace color {

class FColor;

bool nameToRgb(const std::string& cname, FColor*);
std::string rgbToName(const FColor&);

}  // namespace color
}  // namespace fcolor
