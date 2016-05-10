from libcpp cimport bool
from libcpp.string cimport string
from libcpp.vector cimport vector

ctypedef unsigned int uint
ctypedef unsigned char uint8_t

cdef extern from "<tdsp/base/math.h>" namespace "tdsp":
    void clearStruct[T](T&)

include "tdsp/base/wrapper.pyx"
include "tdsp/color/color.pyx"
include "tdsp/color/color_list.pyx"
include "tdsp/signal/_combiner.pyx"
include "tdsp/signal/_render3.pyx"
include "tdsp/signal/_stripe.pyx"
include "tdsp/signal/fade.pyx"
include "tdsp/signal/renderer.pyx"
