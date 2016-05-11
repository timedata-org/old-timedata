#pragma once

#include <set>
#include <string>

#include <tdsp/color/color.h>
#include <tdsp/base/stl.h>

namespace tdsp {

/** Convert a hex number to an RGB color. */
Color toColor(unsigned int);

/** Computational base - 0..1 float or 0..255 integer? */
enum class Base {normal, integer};

/** Convert a Color to a string. */
template <Base base = Base::normal>
std::string toString(Color);

/** Convert a Color to a string. */
template <Base base = Base::normal>
std::string colorToString(float r, float g, float b);

/** Convert a string to a Color.  Throws an exception if the string
    cannot be parsed into a color. */
template <Base base = Base::normal>
Color toColor(char const*);

/** Convert a string to a Color.  Returns true if the conversion succeeded. */
template <Base base = Base::normal>
bool toColor(char const*, Color&);


using ColorNames = std::map<std::string, uint32_t>;
using ColorNamesInverse = std::map<uint32_t, std::string>;

/** Names of hex colors we recognize. */
ColorNames const& colorNames();

/** Best inverse of color names, taking into account secondaryColors. */
ColorNamesInverse const& colorNamesInverse();

/** Alternate color names we recognize. */
std::set<std::string> const& secondaryColors();

} // tdsp
