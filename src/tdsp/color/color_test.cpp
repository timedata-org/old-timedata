#include <tdsp/color/color.h>
#include <tdsp/color2/color.h>
#include <tdsp/color/compare_inl.h>

namespace tdsp {

TEST_CASE("colors", "[color]") {
    auto color8 = clear<Color8>();
    auto colora8 = clear<ColorA8>();
    auto colorf = clear<ColorF>();
    auto coloraf = clear<ColorAF>();
    SECTION("empty") {
        REQUIRE(color8.red == 0);
        REQUIRE(colora8.red == 0);
        REQUIRE(colorf.red == 0);
        REQUIRE(coloraf.red == 0);

        REQUIRE(color8.green == 0);
        REQUIRE(colora8.green == 0);
        REQUIRE(colorf.green == 0);
        REQUIRE(coloraf.green == 0);

        REQUIRE(color8.blue == 0);
        REQUIRE(colora8.blue == 0);
        REQUIRE(colorf.blue == 0);
        REQUIRE(coloraf.blue == 0);

        REQUIRE(colora8.alpha == 255);
        REQUIRE(coloraf.alpha == 1.0);
    }

    SECTION("compare self") {
        REQUIRE(color8 == color8);
        REQUIRE(colora8 == colora8);
        REQUIRE(colorf == colorf);
        REQUIRE(coloraf == coloraf);

        REQUIRE(not (color8 != color8));
        REQUIRE(not (colora8 != colora8));
        REQUIRE(not (colorf != colorf));
        REQUIRE(not (coloraf != coloraf));

        REQUIRE(not (color8 < color8));
        REQUIRE(not (colora8 < colora8));
        REQUIRE(not (colorf < colorf));
        REQUIRE(not (coloraf < coloraf));

        REQUIRE(color8 <= color8);
        REQUIRE(colora8 <= colora8);
        REQUIRE(colorf <= colorf);
        REQUIRE(coloraf <= coloraf);

        REQUIRE(not (color8 > color8));
        REQUIRE(not (colora8 > colora8));
        REQUIRE(not (colorf > colorf));
        REQUIRE(not (coloraf > coloraf));

        REQUIRE(color8 >= color8);
        REQUIRE(colora8 >= colora8);
        REQUIRE(colorf >= colorf);
        REQUIRE(coloraf >= coloraf);
    }

    SECTION("red, green, blue") {
        auto r = red<Color8>();
        REQUIRE(r.red == 255);
        REQUIRE(r.green == 0);
        REQUIRE(r.blue == 0);
    }

    SECTION("mult") {
        auto r = red<ColorF>();
        REQUIRE(r.red == 1.0f);
        REQUIRE(r.green == 0);
        REQUIRE(r.blue == 0);
        r /= 2;
        REQUIRE(r.red == 0.5f);
        REQUIRE(r.green == 0);
        REQUIRE(r.blue == 0);
    }
}

namespace color2 {

TEST_CASE("colors2", "[color]") {
    SECTION("empty") {
        RGB<> c = {0};
        auto red = get<Red>(c);
        REQUIRE(red == 0);

    }
}

}  // namespace color2
}  // namespace tdsp
