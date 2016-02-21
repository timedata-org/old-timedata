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

}

}  // namespace fcolor
