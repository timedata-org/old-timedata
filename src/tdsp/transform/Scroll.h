#pragma once

#include <tdsp/FColorList.h>
#include <tdsp/Transform.h>

namespace tdsp {
namespace color {

class CTransform;

FColorList scroll(const FColorList&, int dx, int dy, int columns, bool wrap);
FColorList smoothScroll(const FColorList&, float dx, float dy, int columns,
                        bool wrap, const CTransform* transform = nullptr);
FColorList smoothScroll(const FColorList&, float dx, float dy, int columns,
                        bool wrap, FloatFunction const&);

}  // namespace color
}  // namespace tdsp
