#pragma once

#include <tada/color/names_inl.h>

namespace tada {
namespace color {

//
TEST_CASE("color", "names") {
    REQUIRE(colorToString(Color{0.5, 0.5, 0.5}, Base::normal) == "gray 50");
    REQUIRE(colorToString(Color{0, 0, 0}, Base::normal) == "black");
    REQUIRE(colorToString(Color{-0.5, 0.5, 0.5}, Base::normal) ==
            "gray 50-++");

    auto c = stringToColor("gray 50-++", Base::normal);
    REQUIRE(c[0] < 0);
    REQUIRE(colorToString(c, Base::normal) == "gray 50-++");
    forEach<Base>([](Base base) {
        for (auto& i : colorMapInverse()) {
            auto c = stringToColor(i.second.c_str(), base);
            REQUIRE(colorToString(c, base) == i.second);
        }
    });
}

} // color
} // tada
