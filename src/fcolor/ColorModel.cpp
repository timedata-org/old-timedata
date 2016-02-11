#include <fcolor/ColorModel.h>
#include <fcolor/FColor.h>
#include <fcolor/HSB.h>
#include <fcolor/RGB.h>

namespace fcolor {
namespace color {

static const ColorModel* const COLOR_MODELS[2] = { new RGB, new HSB };

const ColorModel* ColorModel::getColorModel(ColorModel::Model model) {
    return COLOR_MODELS[model];
}

}  // namespace color
}  // namespace fcolor
