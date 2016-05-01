#include <tdsp/FColor.h>

namespace tdsp {
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
}  // namespace tdsp
