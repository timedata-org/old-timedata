from libcpp cimport bool
from libcpp.map cimport map
from libcpp.string cimport string
from libcpp.vector cimport vector

from libc.stdint cimport uint8_t, uint16_t, uint32_t, uint64_t
from libc.stdint cimport int8_t, int16_t, int32_t, int64_t
ctypedef unsigned int uint

include "src/pyx/timedata/base/math.pyx"
include "src/pyx/timedata/base/wrapper.pyx"
include "src/pyx/timedata/base/timestamp.pyx"
include "src/pyx/timedata/color/colors.pyx"
include "src/pyx/timedata/signal/convert.pyx"
include "build/genfiles/timedata/signal/combiner.pyx"
include "build/genfiles/timedata/signal/fade.pyx"
#include "build/genfiles/timedata/signal/render3.pyx"
include "build/genfiles/timedata/signal/stripe.pyx"

include "build/genfiles/timedata/genfiles.pyx"

locals().update(
     Combiner=_Combiner,
#     Fade=_FadeImpl,
#     Render3=_Render3Impl,
     Stripe=_Stripe,
     )

_load_colors()

print('timedata compiled on', compile_timestamp(), 'with tags', git_tags())
