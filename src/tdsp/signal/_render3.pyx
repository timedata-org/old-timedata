# Automatically generated on 2016-05-11T15:46:21.243086
# by https://github.com/rec/make_pyx/make_pyx.py

cdef extern from "<tdsp/signal/render3.h>" namespace "tdsp::Render3":
    cdef cppclass Permutation:
        pass

cdef extern from "<tdsp/signal/render3.h>" namespace "tdsp::Render3::Permutation":
    cdef Permutation rgb
    cdef Permutation rbg
    cdef Permutation grb
    cdef Permutation gbr
    cdef Permutation brg
    cdef Permutation bgr

Permutation_NAMES = 'rgb', 'rgb', 'etc'

cdef extern from "<tdsp/signal/render3.h>" namespace "tdsp":
    struct Render3:
        float min, max, scale, gamma
        Permutation permutation
        size_t offset, size


cdef class _Render3(_Wrapper):
    cdef Render3 _instance;

    PERMUTATION_NAMES = 'rgb', 'rbg', 'grb', 'gbr', 'brg', 'bgr'

    def __cinit__(self):
        clearStruct(self._instance)

    def clear(self):
        clearStruct(self._instance)

    def __str__(self):
        return "(min=%s, max=%s, scale=%s, gamma=%s, permutation='%s', offset=%s, size=%s)" % (
            self.min, self.max, self.scale, self.gamma, self.permutation, self.offset, self.size)

    property min:
        def __get__(self):
            return self._instance.min
        def __set__(self, float x):
            self._instance.min = x

    property max:
        def __get__(self):
            return self._instance.max
        def __set__(self, float x):
            self._instance.max = x

    property scale:
        def __get__(self):
            return self._instance.scale
        def __set__(self, float x):
            self._instance.scale = x

    property gamma:
        def __get__(self):
            return self._instance.gamma
        def __set__(self, float x):
            self._instance.gamma = x

    property permutation:
        def __get__(self):
            return self.PERMUTATION_NAMES[<int> self._instance.permutation]
        def __set__(self, string x):
            cdef uint8_t i
            i = self.PERMUTATION_NAMES.index(x)
            self._instance.permutation = <Permutation>(i)

    property offset:
        def __get__(self):
            return self._instance.offset
        def __set__(self, size_t x):
            self._instance.offset = x

    property size:
        def __get__(self):
            return self._instance.size
        def __set__(self, size_t x):
            self._instance.size = x
