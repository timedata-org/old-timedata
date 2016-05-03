from libcpp.string cimport string
from libcpp cimport bool

cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp":
    cdef cppclass RGB:
        pass

    cdef cppclass Frame[T]:
        float& at(int)

    bool toColor(const char*, Frame[RGB])
    string colorToString(float r, float g, float b)
    bool cmpToRichcmp(float cmp, int richcmp)

include "tdsp/color/color.pyx"
