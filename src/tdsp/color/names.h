#pragma once

#include <set>
#include <string>

#include <tdsp/color/color.h>
#include <tdsp/base/stl.h>

namespace tdsp {

/** Convert a string to a Color.  Returns true if the conversion succeeded. */
bool stringToColor(char const*, Color&, Base base);
bool stringToColor(char const*, ColorS&, Base base);

/** Convert a string to a Color.  Throws an exception on failure. */
Color stringToColor(char const* name, Base base);

/** Convert a Color to a string. */
std::string colorToString(Color c, Base base);
std::string colorToString(float r, float g, float b);

Color colorFromHex(uint32_t hex, Base base);
uint32_t hexFromColor(Color const& c, Base base);

} // tdsp
