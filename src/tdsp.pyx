from libcpp cimport bool
from libcpp.string cimport string
from libcpp.vector cimport vector

ctypedef unsigned int uint

include "tdsp/base/wrapper.pyx"
include "tdsp/color/color.pyx"
include "tdsp/color/color_list.pyx"
include "tdsp/color/renderer.pyx"
include "tdsp/color/stripe.pyx"
include "tdsp/color/combiner.pyx"
