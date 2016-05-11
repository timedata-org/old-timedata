#pragma once

#include <set>
#include <string>

#include <tdsp/color/color.h>
#include <tdsp/base/stl.h>

namespace tdsp {

/** Computational base - 0..1 float or 0..255 integer? */
enum class Base {normal, integer, size};

/** Convert a string to a Color.  Returns true if the conversion succeeded. */
bool stringToColor(char const*, Color&, Base base);

/** Convert a string to a Color.  Throws an exception on failure. */
Color stringToColor(char const* name, Base base);

/** Convert a Color to a string. */
std::string colorToString(Color c, Base base);
std::string colorToString(float r, float g, float b);

} // tdsp
