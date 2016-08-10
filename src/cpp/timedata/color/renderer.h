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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//
// Implementation details follow.

inline CRenderer::CRenderer(Render3 r)
        : gammaTable_(makeGammaTable(r.gamma, r.min, r.max)),
          perm_(getPerm(r.permutation)) {
}

template <typename Colors>
void CRenderer::renderGeneric(
        float level, Colors const& colors, char* out) {
    for (size_t i = 0; i < colors.size(); ++i) {
        auto color = colors[i];
        for (size_t j = 0; j < color.size(); ++j, ++out) {
            auto component = level * color[perm_[j]];
            auto gamma = getGamma(gammaTable_, component);
            *out = static_cast<char>(gamma);
        }
    }
}

template <typename ColorList>
struct RGBAdaptor {
    ColorList const& list;

    ColorRGB operator[](size_t i) const {
        ColorRGB result;
        converter::convertSample(list[i], result);
        return result;
    };

    size_t size() const { return list.size(); }
};

inline void CRenderer::render(
        float level, CColorListRGB const& colors, char* out) {
    return renderGeneric(level, RGBAdaptor<CColorListRGB>{colors}, out);
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
