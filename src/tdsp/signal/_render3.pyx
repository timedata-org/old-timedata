# Automatically generated on 2016-05-10T22:56:19.806587
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

cdef extern from "<tdsp/signal/render3.h>" namespace "tdsp":
    struct Render3:
        float min, max, scale, gamma
        Permutation permutation
        size_t offset, size


cdef class _Render3(_Wrapper):
    cdef Render3 thisptr;

    PERMUTATION_NAMES = 'rgb', 'rbg', 'grb', 'gbr', 'brg', 'bgr'

    def __cinit__(self):
        clearStruct(self.thisptr)

    def clear(self):
        clearStruct(self.thisptr)

    def __str__(self):
        return "(min=%s, max=%s, scale=%s, gamma=%s, permutation='%s', offset=%s, size=%s)" % (
            self.min, self.max, self.scale, self.gamma, self.permutation, self.offset, self.size)

    property min:
        def __get__(self):
            return self.thisptr.min
        def __set__(self, float x):
            self.thisptr.min = x

    property max:
        def __get__(self):
            return self.thisptr.max
        def __set__(self, float x):
            self.thisptr.max = x

    property scale:
        def __get__(self):
            return self.thisptr.scale
        def __set__(self, float x):
            self.thisptr.scale = x

    property gamma:
        def __get__(self):
            return self.thisptr.gamma
        def __set__(self, float x):
            self.thisptr.gamma = x

    property permutation:
        def __get__(self):
            return self.PERMUTATION_NAMES[<int> self.thisptr.permutation]
        def __set__(self, string x):
            cdef uint8_t i
            i = self.PERMUTATION_NAMES.index(x)
            self.thisptr.permutation = <Permutation>(i)

    property offset:
        def __get__(self):
            return self.thisptr.offset
        def __set__(self, size_t x):
            self.thisptr.offset = x

    property size:
        def __get__(self):
            return self.thisptr.size
        def __set__(self, size_t x):
            self.thisptr.size = x
