#pragma once

#include <timedata/base/gammaTable.h>
#include <timedata/signal/render3.h>
#include <timedata/signal/convert_inl.h>
#include <timedata/color/cython_list_inl.h>

namespace timedata {
namespace color_list {

class CRenderer {
  public:
    CRenderer(Render3);
    CRenderer() = default;
    CRenderer& operator=(CRenderer const&) = default;

    /** Render a CColorListRGB to a byte buffer.  The number of bytes pointed to
        by `out` must be at least 3 times the number of colors. */
    void render(float level, CColorListRGB const&, char* out);

    /** Render a CColorListRGB to a byte buffer.  The number of bytes pointed to
        by `out` must be at least 3 times the number of colors. */
    template <typename Colors>
    void renderGeneric(float level, Colors const&, char* out);

  private:
    using Perm = std::array<uint8_t, 3>;

    static Perm getPerm(Render3::Permutation);

    GammaTable gammaTable_;
    Perm perm_;
};

}  // color_list
}  // timedata
