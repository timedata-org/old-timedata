#pragma once

#include <set>
#include <string>

#include <tada/color/color.h>
#include <tada/base/stl.h>

namespace tada {

/** Convert a string to a Color.  Returns true if the conversion succeeded. */
bool stringToColor(char const*, Color&, Base base);
bool stringToColor(char const*, ColorS&, Base base);
bool stringToColor(char const*, Color&);

/** Convert a string to a Color.  Throws an exception on failure. */
Color stringToColor(char const* name, Base base);

/** Convert a Color to a string. */
std::string colorToString(Color c, Base base);
std::string colorToString(Color c);
std::string colorToString(float r, float g, float b);

Color colorFromHex(uint32_t hex, Base base);
uint32_t hexFromColor(Color const& c, Base base);

} // tada
