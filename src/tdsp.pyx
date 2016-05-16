from libcpp cimport bool
from libcpp.string cimport string
from libcpp.vector cimport vector

ctypedef unsigned int uint
ctypedef unsigned char uint8_t

cdef extern from "<tdsp/base/math.h>" namespace "tdsp":
    void clearStruct[T](T&)

include "tdsp/base/wrapper.pyx"
include "tdsp/color/color.pyx"
include "tdsp/color/operation.pyx"
include "tdsp/color/color_list.pyx"
include "tdsp/color/old_color_list.pyx"
include "tdsp/color/speedtest.pyx"
include "tdsp/signal/_combiner.pyx"
include "tdsp/signal/_stripe.pyx"
include "tdsp/signal/fade.pyx"
include "tdsp/signal/render3.pyx"

locals().update(
    Color=_Color,
    Color256=_Color256,
    ColorList=_ColorList,
    ColorList256=_ColorList256,
    Combiner=_Combiner,
    Fade=_FadeImpl,
    OldColorList=_OldColorList,
    OldColorList256=_OldColorList256,
    Render3=_Render3Impl,
    Stripe=_Stripe,
    )
