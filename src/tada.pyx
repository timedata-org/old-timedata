from libcpp cimport bool
from libcpp.map cimport map
from libcpp.string cimport string
from libcpp.vector cimport vector

from libc.stdint cimport uint32_t, int64_t, uint8_t
ctypedef unsigned int uint

include "tada/base/math.pyx"
include "tada/base/wrapper.pyx"
include "tada/base/timestamp.pyx"
include "tada/color/color_base.pyx"
include "tada/color/color.pyx"
include "tada/color/color256.pyx"
include "tada/color/color_list_base.pyx"
include "tada/color/color_list.pyx"
include "tada/color/color_list256.pyx"
include "tada/color/colors.pyx"
include "tada/signal/_combiner.pyx"
include "tada/signal/_stripe.pyx"
include "tada/signal/fade.pyx"
include "tada/signal/render3.pyx"

locals().update(
    Combiner=_Combiner,
    Fade=_FadeImpl,
    Render3=_Render3Impl,
    Stripe=_Stripe,
    )

_load_colors()

print('tada compiled on', compile_timestamp(), 'with tags', git_tags())
