#pragma once

#include <timedata/base/gammaTable.h>
#include <timedata/signal/render3.h>
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
    void render(float level, CColorListRGB const& colors, char* out);

  private:
    using Perm = std::array<uint8_t, 3>;

    static Perm getPerm(Render3::Permutation);

    GammaTable gammaTable_;
    Perm perm_;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Implementation details follow.

inline CRenderer::CRenderer(Render3 r)
        : gammaTable_(makeGammaTable(r.gamma, r.min, r.max)),
          perm_(getPerm(r.permutation)) {
}

/** Render a CColorListRGB to a byte buffer.  The number of bytes pointed to
    by `out` must be at least 3 times the number of colors. */
inline void CRenderer::render(float level, CColorListRGB const& colors,
                             char* out) {
    for (size_t i = 0; i < colors.size(); ++i) {
        for (size_t j = 0; j < colors[i].size(); ++j, ++out) {
            auto component = level * colors[i][perm_[j]];
            auto gamma = getGamma(gammaTable_, component);
            *out = static_cast<char>(gamma);
        }
    }
}

inline CRenderer::Perm CRenderer::getPerm(Render3::Permutation perm) {
    static std::vector<Perm> const PERMS = {
        {{0, 1, 2}},
        {{0, 2, 1}},
        {{1, 0, 2}},
        {{1, 2, 0}},
        {{2, 0, 1}},
        {{2, 1, 0}}};
    return PERMS[static_cast<int>(perm)];
}

}
}
