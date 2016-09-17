#pragma once

#include <cstddef>
#include <timedata/base/gammaTable.h>
#include <timedata/color/cython_list_inl.h>
#include <timedata/color/render3.h>
#include <timedata/signal/convert_inl.h>

namespace timedata {
namespace color_list {

class CRenderer {
  public:
    CRenderer(Render3);
    CRenderer() = default;
    CRenderer& operator=(CRenderer const&) = default;

    /** Render a generic RGBIndexer to a byte buffer.  The number of bytes
        pointed to by `out` must be at least 3 times the number of colors. */
    void render(
        float level, RGBIndexer const&, size_t pos, size_t size, char* out);

  private:
    using Perm = std::array<uint8_t, 3>;

    static Perm getPerm(Render3::Permutation);

    GammaTable gammaTable_;
    Perm perm_;
    size_t prefix_;
};

}  // color_list
}  // timedata
