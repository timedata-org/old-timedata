#include <fcolor/FColor.h>

namespace fcolor {
namespace color {

namespace {

const FColor make_black() {
    FColor black;
    black.clear();
    return black;
}

}

const FColor FColor::BLACK = make_black();

}  // namespace color
}  // namespace fcolor
