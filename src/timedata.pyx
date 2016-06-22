from libcpp cimport bool
from libcpp.map cimport map
from libcpp.string cimport string
from libcpp.vector cimport vector

from libc.stdint cimport uint32_t, int64_t, uint8_t
ctypedef unsigned int uint

include "timedata/base/math.pyx"
include "timedata/base/wrapper.pyx"
include "timedata/base/timestamp.pyx"
include "timedata/color/color_base.pyx"
include "timedata/color/color.pyx"
include "timedata/color/color256.pyx"
include "timedata/color/color_list_base.pyx"
include "timedata/color/color_list.pyx"
include "timedata/color/color_list256.pyx"
include "timedata/color/colors.pyx"
include "timedata/signal/_combiner.pyx"
include "timedata/signal/_stripe.pyx"
include "timedata/signal/fade.pyx"
include "timedata/signal/render3.pyx"

include "timedata/template/genfiles.pyx"

locals().update(
    Combiner=_Combiner,
    Fade=_FadeImpl,
    Render3=_Render3Impl,
    Stripe=_Stripe,
    )

_load_colors()

print('timedata compiled on', compile_timestamp(), 'with tags', git_tags())
