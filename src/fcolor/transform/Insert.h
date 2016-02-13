#pragma once

#include <fcolor/FColorList.h>

namespace fcolor {
namespace color {

FColorList insert(const FColorList& fcl,
                  int offset, uint length, bool rollover, int skip);

}  // namespace color
}  // namespace fcolor
