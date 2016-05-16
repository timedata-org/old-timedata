#pragma once

#include <map>
#include <string>

namespace tdsp {

using ColorMap = std::map<std::string, uint32_t>;
using ColorMapInverse = std::map<uint32_t, std::string>;
using ColorNames = std::set<std::string>;

/** Names of hex colors we recognize. */
ColorMap const& colorMap();

/** Names of hex colors we recognize. */
ColorNames const& colorNames();

/** Best inverse of color map, taking into account secondaryColors. */
ColorMapInverse const& colorMapInverse();

/** Alternate color names we recognize. */
ColorNames const& secondaryColors();

}  // tdsp
