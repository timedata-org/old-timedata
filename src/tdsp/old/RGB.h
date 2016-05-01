#pragma once

#include <tdsp/FColor.h>
#include <tdsp/ColorModel.h>
#include <tdsp/ColorName.h>

namespace tdsp {
namespace color {

class RGB : public ColorModel {
  public:
    FColor toRgb(const FColor& color) const override {
        return color;
    }

    FColor fromRgb(const FColor& color) const override {
        return color;
    }

    std::string modelName() const override { return "rgb"; }

    bool isRgb() const override { return true; }

    FColor interpolate(
        const FColor& begin, const FColor& end, float ratio) const override {
        return begin.interpolate(end, ratio);
    }

    static const float& red(const FColor& fc) { return fc.red(); }
    static const float& green(const FColor& fc) { return fc.green(); }
    static const float& blue(const FColor& fc) { return fc.blue(); }

    static float& red(FColor& fc) { return fc.red(); }
    static float& green(FColor& fc) { return fc.green(); }
    static float& blue(FColor& fc) { return fc.blue(); }
};

}  // namespace color
}  // namespace tdsp
