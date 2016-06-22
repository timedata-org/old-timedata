#pragma once

#include <string>

namespace timedata {

/** Search and replace in a string. */
std::string replace(std::string subject,
                    std::string const& search,
                    std::string const& replace);

/** Lowercase a string in-place. */
void lower(std::string& subject);

/** Return a float as "x.xxx". */
std::string toString(float);

/** Return a float as "xx.x or 100.0". */
std::string toPercent(float);

bool isHex(const std::string&);

}  // namespace timedata
