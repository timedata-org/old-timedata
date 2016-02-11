#pragma once

#include <fcolor/Fcolor.h>

namespace fcolor {
namespace color {

inline int computeRows(int size, int columns) {
    return size / columns + ((size % columns) ? 1 : 0);
}

}  // namespace color
}  // namespace fcolor
