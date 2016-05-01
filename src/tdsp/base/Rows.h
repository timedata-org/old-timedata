#pragma once

#include <tdsp/Fcolor.h>

namespace tdsp {
namespace color {

inline int computeRows(int size, int columns) {
    return size / columns + ((size % columns) ? 1 : 0);
}

}  // namespace color
}  // namespace tdsp
