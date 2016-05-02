#pragma once

#include <string>

#include <tdsp/color/color.h>

namespace tdsp {

/** Convert a hex number to an RGB color. */
Frame<RGB> toColor(unsigned int);

/** Convert a Color to a string. */
std::string toString(Frame<RGB>);

/** Convert a Color to a comma-separated triple of floats. */
std::string toCommaSeparated(Frame<RGB>);

/** Convert a string to a Color.  Throws an exception if the string
    cannot be parsed into a color. */
Frame<RGB> toColor(std::string const&);

} // tdsp
