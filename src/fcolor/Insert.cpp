#include <fcolor/Insert.h>
#include <fcolor/Math.h>

namespace fcolor {
namespace color {

FColorList insert(const FColorList& fcl,
                  int offset, uint length, bool rollover, int skip) {
    FColorList result;
    result.resize(length);
    for (auto& color: fcl) {
        result[mod(offset, length)] = color;
        offset += skip;
    }
    return result;
}

}  // namespace color
}  // namespace fcolor
