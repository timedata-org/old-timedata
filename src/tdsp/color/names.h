#pragma once

#include <set>
#include <string>

#include <tdsp/color/color.h>
#include <tdsp/base/stl.h>

namespace tdsp {

/** Computational base - 0..1 float or 0..255 integer? */
enum class Base {normal, integer};

/** Convert a string to a Color.  Returns true if the conversion succeeded. */
template <Base base = Base::normal>
bool toColor(char const*, Color&);

/** Convert a string to a Color.  Throws an exception on failure. */
template <Base base = Base::normal>
Color toColor(char const* name);

/** Convert a Color to a string. */
template <Base base = Base::normal>
std::string toString(Color c);

/** Convert a Color to a string. */
template <Base base = Base::normal>
std::string colorToString(float r, float g, float b);

} // tdsp
