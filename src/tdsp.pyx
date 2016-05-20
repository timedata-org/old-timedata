from libcpp cimport bool
from libcpp.map cimport map
from libcpp.string cimport string
from libcpp.vector cimport vector

from libc.stdint cimport uint32_t, int64_t, uint8_t
ctypedef unsigned int uint

include "tdsp/base/math.pyx"
include "tdsp/base/wrapper.pyx"
include "tdsp/base/timestamp.pyx"
include "tdsp/color/color_base.pyx"
include "tdsp/color/color.pyx"
include "tdsp/color/color256.pyx"
include "tdsp/color/color_list_base.pyx"
include "tdsp/color/color_list.pyx"
include "tdsp/color/color_list256.pyx"
include "tdsp/color/colors.pyx"
include "tdsp/signal/_combiner.pyx"
include "tdsp/signal/_stripe.pyx"
include "tdsp/signal/fade.pyx"
include "tdsp/signal/render3.pyx"

locals().update(
    Combiner=_Combiner,
    Fade=_FadeImpl,
    Render3=_Render3Impl,
    Stripe=_Stripe,
    )

_load_colors()

print('tdsp compiled on', compile_timestamp())
