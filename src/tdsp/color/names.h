#pragma once

#include <set>
#include <string>

#include <tdsp/color/color.h>
#include <tdsp/base/stl.h>

namespace tdsp {

/** Computational base - 0..1 float or 0..255 integer? */
enum class Base {normal, integer};

/** Convert a string to a Color.  Returns true if the conversion succeeded. */
bool toColor(char const*, Color&, Base base = Base::normal);

/** Convert a string to a Color.  Throws an exception on failure. */
Color toColor(char const* name, Base base = Base::normal);

/** Convert a Color to a string. */
std::string colorToString(Color c, Base base = Base::normal);
std::string colorToString(float r, float g, float b, Base base = Base::normal);

} // tdsp
