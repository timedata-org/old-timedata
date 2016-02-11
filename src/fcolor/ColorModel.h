#pragma once

#include <fcolor/Fcolor.h>

namespace fcolor {
namespace color {

class FColor;

class ColorModel {
  public:
    ColorModel() {}
    virtual ~ColorModel() {}

    virtual FColor interpolate(
        const FColor& begin, const FColor& end, float ratio) const = 0;

    virtual bool isRgb() const = 0;
    virtual FColor toRgb(const FColor&) const = 0;
    virtual FColor fromRgb(const FColor&) const = 0;
    virtual std::string modelName() const = 0;

    enum Model { RGB, HSB };
    static const ColorModel* getColorModel(Model);
};

}  // namespace color
}  // namespace fcolor
