#pragma once

#include <timedata/color/color.h>

namespace timedata {

Color rgbToHsv(Color);
Color hsvToRgb(Color);
Color rgbToHsv(Color, Base);
Color hsvToRgb(Color, Base);

} // timedata
