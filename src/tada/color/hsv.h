#pragma once

#include <tada/color/color.h>

namespace tada {

Color rgbToHsv(Color);
Color hsvToRgb(Color);
Color rgbToHsv(Color, Base);
Color hsvToRgb(Color, Base);

} // tada
