cdef extern from "<tdsp/color/combiner.h>" namespace "tdsp":
    struct Combiner:
        float scale, offset
        uint mute, invert


cdef class _Combiner:
    cdef Combiner _combiner;

    property scale:
        def __get__(self):            return self._combiner.scale
        def __set__(self, float x):   self._combiner.scale = x

    property offset:
        def __get__(self):            return self._combiner.offset
        def __set__(self, float x):   self._combiner.offset = x

    property mute:
        def __get__(self):            return self._combiner.mute
        def __set__(self, uint x):    self._combiner.mute = x

    property invert:
        def __get__(self):            return self._combiner.invert
        def __set__(self, uint x):    self._combiner.invert = x


globals()['Color'] = _Color
