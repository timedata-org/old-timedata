# Automatically generated on 2016-05-09T21:08:12.838894
# by https://github.com/rec/make_pyx/make_pyx.py

cdef extern from "<tdsp/color/render3.h>" namespace "tdsp":
    struct Render3:
        float min, max, scale, gamma
        uint8_t permutation
        char* buffer
        size_t offset, size

cdef class _Render3(_Wrapper):
    cdef Render3 _render3;

    def __str__(self):
        return '(min=%s, max=%s, scale=%s, gamma=%s, permutation=%s, buffer=%s, offset=%s, size=%s)' % (
            self.min, self.max, self.scale, self.gamma, self.permutation, self.buffer, self.offset, self.size)

    property min:
        def __get__(self):
            return self._render3.min
        def __set__(self, float x):
            self._render3.min = x

    property max:
        def __get__(self):
            return self._render3.max
        def __set__(self, float x):
            self._render3.max = x

    property scale:
        def __get__(self):
            return self._render3.scale
        def __set__(self, float x):
            self._render3.scale = x

    property gamma:
        def __get__(self):
            return self._render3.gamma
        def __set__(self, float x):
            self._render3.gamma = x

    property permutation:
        def __get__(self):
            return self._render3.permutation
        def __set__(self, uint8_t x):
            self._render3.permutation = x

    property buffer:
        def __get__(self):
            return self._render3.buffer
        def __set__(self, char* x):
            self._render3.buffer = x

    property offset:
        def __get__(self):
            return self._render3.offset
        def __set__(self, size_t x):
            self._render3.offset = x

    property size:
        def __get__(self):
            return self._render3.size
        def __set__(self, size_t x):
            self._render3.size = x


globals()['Render3'] = _Render3
