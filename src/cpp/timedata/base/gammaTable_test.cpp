#pragma once

#include <timedata/base/gammaTable.h>

namespace timedata {

/**

filler here to make tests work.

*/

TEST_CASE("gammaTable Identity") {
    auto table = makeGammaTable(1.0f);
    REQUIRE(table.size() == 1024);
    REQUIRE(getGamma(table, 0) == 0);
    REQUIRE(getGamma(table, 1) == 255);

    for (size_t i = 0; i < 256; i++)
        REQUIRE(i == getGamma(table, i / 255.0f));
}

TEST_CASE("gammaTable full") {
    auto table = makeGammaTable(2.5f);
    REQUIRE(table.size() == 2556);
    REQUIRE(getGamma(table, 0) == 0);
    REQUIRE(getGamma(table, 1) == 0xFF);

    for (size_t i = 1; i < 0xFF; i++) {
        // Make sure the value in the middle of the range is right.
        auto f = std::pow((i + 0.5f) / 256.0f, 1.0f / 2.5f);
        REQUIRE(i == getGamma(table, f));
    }
}

void testGamma(float gamma, size_t size) {
    auto table = makeGammaTable(gamma, 0x80, 0xFF);
    REQUIRE(table.size() == size);
    REQUIRE(getGamma(table, 0) == 0x80);
    REQUIRE(getGamma(table, 1) == 0xFF);

    for (size_t i = 0x81; i < 0xFF; i++) {
        // Check the middle of each range.
        auto scaled = 2.0f * (i - 0x80);
        auto f = std::pow((scaled + 0.5f) / 256.0f, 1.0f / gamma);
        REQUIRE(i == getGamma(table, f));
    }
}

TEST_CASE("gammaTable LPD") {
    testGamma(2.5f, 2556);
}

} // timedata
