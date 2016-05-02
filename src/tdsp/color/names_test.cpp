#pragma once

#include <tdsp/color/names_inl.h>

namespace tdsp {

TEST_CASE("color", "names") {
   REQUIRE(toString(Frame<RGB>{{0, 0, 0}}) == "black");
}

} // namespace
