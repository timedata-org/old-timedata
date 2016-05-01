#pragma once

#include <tdsp/FColorList.h>

namespace tdsp {
namespace color {

FColorList insert(const FColorList& fcl,
                  int offset, uint length, bool rollover, int skip);

}  // namespace color
}  // namespace tdsp
