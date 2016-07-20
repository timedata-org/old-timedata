#pragma once

#include <timedata/base/gammaTable.h>

namespace timedata {

/**

filler here to make tests work.

*/

TEST_CASE("gammaTable Identity") {
    GammaTable table(1.0f);
    REQUIRE(table.table.size() == 1024);
    REQUIRE(table(0) == 0);
    REQUIRE(table(1) == 255);

    for (size_t i = 0; i < 256; i++)
        REQUIRE(i == table(i / 255.0f));
}

// not quite working yet...
TEST_CASE("gammaTable stuff") {
    GammaTable table(2.5f);
    REQUIRE(table.table.size() == 2556);
    REQUIRE(table(0) == 0);
    REQUIRE(table(1) == 255);

    for (size_t i = 1; i < 255; i++) {
        auto f = std::pow((i + 0.5f) / 256.0f, 1.0f / 2.5f);
        log(i, f, int(table(f)));
        REQUIRE(i == table(f));
    }
}

} // timedata
