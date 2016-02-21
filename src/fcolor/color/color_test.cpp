namespace fcolor {

TEST_CASE("colors in general", "[color]") {
    auto color8 = clear<Color8>();
    auto colora8 = clear<ColorA8>();
    auto colorf = clear<ColorF>();
    auto coloraf = clear<ColorAF>();

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

}  // namespace fcolor
