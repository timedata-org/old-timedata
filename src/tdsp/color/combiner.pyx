# Automatically generated on 2016-05-09T23:37:22.656817
# by https://github.com/rec/make_pyx/make_pyx.py

cdef extern from "<tdsp/color/combiner.h>" namespace "tdsp":
    struct Combiner:
        float scale, offset
        uint mute
        uint invert
    void clearStruct(Combiner&)

cdef class _Combiner(_Wrapper):
    cdef Combiner _combiner;

    def __cinit__(self):
        clearStruct(self._combiner)

    def clear(self):
        clearStruct(self._combiner)

    def __str__(self):
        return '(scale=%s, offset=%s, mute=%s, invert=%s)' % (
            self.scale, self.offset, self.mute, self.invert)

    property scale:
        def __get__(self):
            return self._combiner.scale
        def __set__(self, float x):
            self._combiner.scale = x

    property offset:
        def __get__(self):
            return self._combiner.offset
        def __set__(self, float x):
            self._combiner.offset = x

    property mute:
        def __get__(self):
            return self._combiner.mute
        def __set__(self, uint x):
            self._combiner.mute = x

    property invert:
        def __get__(self):
            return self._combiner.invert
        def __set__(self, uint x):
            self._combiner.invert = x
