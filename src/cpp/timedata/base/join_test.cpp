#pragma once

#include <timedata/base/join_inl.h>

namespace timedata {

TEST_CASE("join", "All") {
    REQUIRE(join() == "");
    REQUIRE(join("test") == "test");
    REQUIRE(join(5) == "5");
    REQUIRE(join(5, 1, 2, 6) == "5126");
    REQUIRE(join(5, "1", 2, 6.14) == "5126.14");
}

TEST_CASE("joinSpace", "All") {
    REQUIRE(joinSpace() == "");
    REQUIRE(joinSpace("test") == "test");
    REQUIRE(joinSpace(5) == "5");
    REQUIRE(joinSpace(5, 1, 2, 6) == "5 1 2 6");
    REQUIRE(joinSpace(5, "1", 2, 6.14) == "5 1 2 6.14");
}

} // timedata
