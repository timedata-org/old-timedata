#pragma once

#include <map>
#include <string>

namespace tdsp {

using ColorNames = std::map<std::string, uint32_t>;
using ColorNamesInverse = std::map<uint32_t, std::string>;

/** Names of hex colors we recognize. */
ColorNames const& colorNames();

/** Best inverse of color names, taking into account secondaryColors. */
ColorNamesInverse const& colorNamesInverse();

/** Alternate color names we recognize. */
std::set<std::string> const& secondaryColors();

}  // tdsp
