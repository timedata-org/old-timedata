#pragma once

#include <string>

#include <tdsp/color/color.h>

namespace tdsp {

/** Convert a Color to a string. */
std::string toString(Frame<RGB>);

/** Convert a string to a Color.  Throws an exception if the string
    cannot be parsed into a color. */
Frame<RGB> toColor(std::string const&);

} // tdsp
