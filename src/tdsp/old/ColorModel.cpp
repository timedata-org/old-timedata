#include <tdsp/ColorModel.h>
#include <tdsp/FColor.h>
#include <tdsp/HSB.h>
#include <tdsp/RGB.h>

namespace tdsp {
namespace color {

static const ColorModel* const COLOR_MODELS[2] = { new RGB, new HSB };

const ColorModel* ColorModel::getColorModel(ColorModel::Model model) {
    return COLOR_MODELS[model];
}

}  // namespace color
}  // namespace tdsp
