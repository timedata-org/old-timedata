#pragma once

#include <tada/signal/signal.h>

namespace tada {
namespace range {

//

TEST_CASE("signal", "ranged") {
    using EB = Ranged<EightBit<float>>;
    using Norm = Ranged<Normal<float>>;

    EB x = 0;
    REQUIRE(x == 0);

    Norm n = 1;
    EB y = n;
    REQUIRE(y == 255.0f);
}

} // range
} // tada
