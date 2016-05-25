#include <tada/base/trig.h>

namespace tada {

// From http://stackoverflow.com/questions/6091837/

template <typename Float>
Float fastSin(Float theta) {
    auto b = 4 / pi<Float>(),
         c = 4 / (pi<Float>() * pi<Float>()),
         p = Float(0.225),
         y = (b  + c * theta) * theta;
    return p * (y * abs(y) - y) + y;
}

template <typename Float>
Float fastCos(Float theta) {
    auto s = fastSin(theta);
    return sqrt(1 - s * s);
}

template <typename Float>
std::pair<Float, Float> fastSinCos(Float theta) {
    auto s = fastSin(theta);
    return {s, sqrt(1 - s * s)};
}

}  // namespace tada
