# Automatically generated on 2016-05-10T19:17:47.154432
# by https://github.com/rec/make_pyx/make_pyx.py



cdef extern from "<tdsp/color/combiner.h>" namespace "tdsp":
    struct Combiner:
        float scale, offset
        uint mute
        uint invert


cdef class _Combiner(_Wrapper):
    cdef Combiner thisptr;

    def __cinit__(self):
        clearStruct(self.thisptr)

    def clear(self):
        clearStruct(self.thisptr)

    def __str__(self):
        return '(scale=%s, offset=%s, mute=%s, invert=%s)' % (
            self.scale, self.offset, self.mute, self.invert)

    property scale:
        def __get__(self):
            return self.thisptr.scale
        def __set__(self, float x):
            self.thisptr.scale = x

    property offset:
        def __get__(self):
            return self.thisptr.offset
        def __set__(self, float x):
            self.thisptr.offset = x

    property mute:
        def __get__(self):
            return self.thisptr.mute
        def __set__(self, uint x):
            self.thisptr.mute = x

    property invert:
        def __get__(self):
            return self.thisptr.invert
        def __set__(self, uint x):
            self.thisptr.invert = x
