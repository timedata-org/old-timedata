# Automatically generated on 2016-05-10T19:23:23.752407
# by https://github.com/rec/make_pyx/make_pyx.py

cdef extern from "<tdsp/color/render3.h>" namespace "tdsp":
    struct Render3:
        float min, max, scale, gamma
        uint8_t permutation
        size_t offset, size


cdef class _Render3(_Wrapper):
    cdef Render3 thisptr;

    def __cinit__(self):
        clearStruct(self.thisptr)

    def clear(self):
        clearStruct(self.thisptr)

    def __str__(self):
        return '(min=%s, max=%s, scale=%s, gamma=%s, permutation=%s, offset=%s, size=%s)' % (
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
            return self.thisptr.permutation
        def __set__(self, uint8_t x):
            self.thisptr.permutation = x

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
