#pragma once

#include <tdsp/base/math.h>

namespace tdsp {

enum class FadeType {linear, sqr, sqrt, exp, log};

struct Fade {
    float begin = 0, end = 1;
    float speed = 1;
    uint8_t type = static_cast<uint8_t>(FadeType::linear);
};

} // tdsp
