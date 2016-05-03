#pragma once

#include <tdsp/color/names_inl.h>

namespace tdsp {
namespace color {

TEST_CASE("color", "names") {
   REQUIRE(toString(Frame<RGB>{{0.5, 0.5, 0.5}}) == "gray 50");
   REQUIRE(toString(Frame<RGB>{{0, 0, 0}}) == "black");

   for (auto& i : colorNamesInverse())
       REQUIRE(toString(toColor(i.second.c_str())) == i.second);
}

} // color
} // tdsp
