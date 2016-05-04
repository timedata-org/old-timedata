#pragma once

#include <tdsp/color/names_inl.h>

namespace tdsp {
namespace color {

TEST_CASE("color", "names") {
   REQUIRE(toString(Color{{0.5, 0.5, 0.5}}) == "gray 50");
   REQUIRE(toString(Color{{0, 0, 0}}) == "black");
   REQUIRE(toString(Color{{-0.5, 0.5, 0.5}}) == "gray 50-++");

   auto c = toColor("gray 50-++");
   REQUIRE(c[0] < 0);
   REQUIRE(toString(c) == "gray 50-++");
   for (auto& i : colorNamesInverse())
       REQUIRE(toString(toColor(i.second.c_str())) == i.second);

}

} // color
} // tdsp
