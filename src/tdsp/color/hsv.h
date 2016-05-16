#pragma once

#include <tdsp/color/color.h>

namespace tdsp {

Color rgbToHsv(Color);
Color hsvToRgb(Color);
Color rgbToHsv(Color, Base);
Color hsvToRgb(Color, Base);

} // tdsp
