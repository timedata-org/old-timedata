#include <tdsp/Insert.h>
#include <tdsp/Math.h>

namespace tdsp {
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
}  // namespace tdsp
