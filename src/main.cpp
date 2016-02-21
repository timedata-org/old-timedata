#include <fcolor/base/level_inl.h>
#include <fcolor/base/number_inl.h>
#include <fcolor/base/string_inl.h>
#include <fcolor/base/trig_inl.h>
#include <fcolor/color/color_inl.h>
#include <fcolor/color/names_inl.h>
#include <fcolor/color/pack_inl.h>

int main() {
    auto c = fcolor::color(1, 2, 3);
    auto d = fcolor::color(1, 2, 3, 0);
    return c.green + d.red;
}
