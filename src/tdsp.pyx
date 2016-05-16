from libcpp cimport bool
from libcpp.string cimport string
from libcpp.vector cimport vector

ctypedef unsigned int uint
ctypedef unsigned char uint8_t

# TODO: these need to go somewhere much better.
cdef extern from "<tdsp/base/math.h>" namespace "tdsp":
    void clearStruct[T](T&)

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp":
    cppclass ColorList:
        Color& operator[](size_t)
        size_t size()
        void resize(size_t)
        void clear();
        bool fixKey(int& key)
        void setColor(size_t, float r, float g, float b)
        bool getColor(size_t , float r, float g, float b)


include "tdsp/base/wrapper.pyx"
include "tdsp/color/color.pyx"
include "tdsp/color/operation.pyx"
#include "tdsp/color/correct_color_list.pyx"
include "tdsp/color/color_list.pyx"
include "tdsp/color/operator_color_list.pyx"
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
    Render3=_Render3Impl,
    Stripe=_Stripe,
    )
