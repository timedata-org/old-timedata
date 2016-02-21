#include <fcolor/inl.h>

int main() {
    auto c = fcolor::color(1, 2, 3);
    auto d = fcolor::color(1, 2, 3, 0);
    return c.green + d.red;
}
