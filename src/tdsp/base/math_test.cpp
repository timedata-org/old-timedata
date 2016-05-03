#pragma once

#include <tdsp/base/math_inl.h>

namespace tdsp {
namespace math {

TEST_CASE("math", "toString") {
    REQUIRE(toString(0, 7) == "0");
    REQUIRE(toString(0) == "0");
    REQUIRE(toString(0.1) == "0");
    REQUIRE(toString(0.1, 1) == "0.1");
    REQUIRE(toString(0.1, 2) == "0.1");
    REQUIRE(toString(0.11, 2) == "0.11");
    REQUIRE(toString(-10, 0) == "-10");
    REQUIRE(toString(-10, 2) == "-10");
    REQUIRE(toString(-10.236, 2) == "-10.24");
}

} // math
} // tdsp
