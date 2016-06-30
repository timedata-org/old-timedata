from libcpp cimport bool
from libcpp.map cimport map
from libcpp.string cimport string
from libcpp.vector cimport vector

from libc.stdint cimport uint32_t, int64_t, uint8_t
ctypedef unsigned int uint

include "src/pyx/timedata/base/math.pyx"
include "src/pyx/timedata/base/wrapper.pyx"
include "src/pyx/timedata/base/timestamp.pyx"
include "src/pyx/timedata/color/colors.pyx"
include "build/genfiles/timedata/signal/combiner.pyx"
include "build/genfiles/timedata/signal/stripe.pyx"
#include "src/pyx/timedata/signal/fade.pyx"
#include "src/pyx/timedata/signal/render3.pyx"

include "build/genfiles/timedata/genfiles.pyx"

locals().update(
     Combiner=_Combiner,
#     Fade=_FadeImpl,
#     Render3=_Render3Impl,
     Stripe=_Stripe,
     )

_load_colors()

print('timedata compiled on', compile_timestamp(), 'with tags', git_tags())
