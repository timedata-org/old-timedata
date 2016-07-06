#pragma once

#include <map>
#include <set>
#include <string>

namespace timedata {

using ColorMap = std::map<std::string, uint32_t>;
using ColorMapInverse = std::map<int, std::string>;
using ColorNames = std::set<std::string>;

/** Names of hex colors we recognize. */
ColorMap const& colorMap();

/** Names of hex colors we recognize. */
std::vector<std::string> const& colorNames();

/** Best inverse of color map, taking into account secondaryColors. */
ColorMapInverse const& colorMapInverse();

/** Alternate color names we recognize. */
ColorNames const& secondaryColors();

}  // timedata
