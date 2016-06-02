#pragma once

#include <tada/color/color.h>

namespace tada {
namespace color {

TEST_CASE("Color", "access") {
    using Color = RGBModel;
    Color c;
    REQUIRE(&c.sample[0] == &c.field.red);
    REQUIRE(&c.sample[1] == &c.field.green);
    REQUIRE(&c.sample[2] == &c.field.blue);

    c.field.red = 1.0f;
    c.field.green = 0.5f;
    c.field.blue = 0.25f;

    REQUIRE(c.sample[0] == c.field.red);
    REQUIRE(c.sample[1] == c.field.green);
    REQUIRE(c.sample[2] == c.field.blue);

    {
        Color c2(1.0f, 0.5f, 0.25f);
        REQUIRE(c.sample[0] == c2.field.red);
        REQUIRE(c.sample[1] == c2.field.green);
        REQUIRE(c.sample[2] == c2.field.blue);
    }
    {
        Color c2;
        REQUIRE(c2.sample[0] == 0.0f);
        REQUIRE(c2.sample[1] == 0.0f);
        REQUIRE(c2.sample[2] == 0.0f);
        REQUIRE(c2.field.red == 0.0f);
        REQUIRE(c2.field.green == 0.0f);
        REQUIRE(c2.field.blue == 0.0f);
    }
}

} // color
} // tada
