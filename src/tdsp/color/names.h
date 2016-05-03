#pragma once

#include <set>
#include <string>

#include <tdsp/color/color.h>
#include <tdsp/base/stl.h>

namespace tdsp {

/** Convert a hex number to an RGB color. */
Sample<RGB> toColor(unsigned int);

/** Convert a Color to a string. */
std::string toString(Sample<RGB>);

/** Convert a Color to a string. */
std::string colorToString(float r, float g, float b);

/** Convert a string to a Color.  Throws an exception if the string
    cannot be parsed into a color. */
Sample<RGB> toColor(char const*);

/** Convert a string to a Color.  Returns true if the conversion succeeded. */
bool toColor(char const*, Sample<RGB>&);


using ColorNames = std::map<std::string, uint32_t>;
using ColorNamesInverse = std::map<uint32_t, std::string>;

/** Names of hex colors we recognize. */
ColorNames const& colorNames();

/** Best inverse of color names, taking into account secondaryColors. */
ColorNamesInverse const& colorNamesInverse();

/** Alternate color names we recognize. */
std::set<std::string> const& secondaryColors();

} // tdsp
