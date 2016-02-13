#pragma once

#include <fcolor/FColorList.h>
#include <fcolor/Transform.h>

namespace fcolor {
namespace color {

class CTransform;

FColorList scroll(const FColorList&, int dx, int dy, int columns, bool wrap);
FColorList smoothScroll(const FColorList&, float dx, float dy, int columns,
                        bool wrap, const CTransform* transform = nullptr);
FColorList smoothScroll(const FColorList&, float dx, float dy, int columns,
                        bool wrap, FloatFunction const&);

}  // namespace color
}  // namespace fcolor
