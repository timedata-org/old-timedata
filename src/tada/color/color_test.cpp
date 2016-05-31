#pragma once

#include <tada/color/color.h>

namespace tada {
namespace color {

TEST_CASE("Color", "access") {
    using Color = Access<RGB>;
    Color c;
    REQUIRE(&c.sample[0] == &c.names.red);
    REQUIRE(&c.sample[1] == &c.names.green);
    REQUIRE(&c.sample[2] == &c.names.blue);

    c.names.red = 1.0f;
    c.names.green = 0.5f;
    c.names.blue = 0.25f;

    REQUIRE(c.sample[0] == c.names.red);
    REQUIRE(c.sample[1] == c.names.green);
    REQUIRE(c.sample[2] == c.names.blue);

    {
        Color c2({1.0f, 0.5f, 0.25f});
        REQUIRE(c.sample[0] == c2.names.red);
        REQUIRE(c.sample[1] == c2.names.green);
        REQUIRE(c.sample[2] == c2.names.blue);
    }
    {
        Color c2;
        REQUIRE(c2.sample[0] == 0.0f);
        REQUIRE(c2.sample[1] == 0.0f);
        REQUIRE(c2.sample[2] == 0.0f);
        REQUIRE(c2.names.red == 0.0f);
        REQUIRE(c2.names.green == 0.0f);
        REQUIRE(c2.names.blue == 0.0f);
    }
}

} // color
} // tada
