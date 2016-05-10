# Automatically generated on 2016-05-10T16:28:32.260679
# by https://github.com/rec/make_pyx/make_pyx.py

cdef extern from "<tdsp/color/fade.h>" namespace "tdsp":
    struct Fade:
        float begin, end, fader
        uint8_t type

    void clear(Fade&)


cdef class _Fade(_Wrapper):
    cdef Fade _fade;

    def __cinit__(self):
        clear(self._fade)

    def clear(self):
        clear(self._fade)

    def __str__(self):
        return '(begin=%s, end=%s, fader=%s, type=%s)' % (
            self.begin, self.end, self.fader, self.type)

    property begin:
        def __get__(self):
            return self._fade.begin
        def __set__(self, float x):
            self._fade.begin = x

    property end:
        def __get__(self):
            return self._fade.end
        def __set__(self, float x):
            self._fade.end = x

    property fader:
        def __get__(self):
            return self._fade.fader
        def __set__(self, float x):
            self._fade.fader = x

    property type:
        def __get__(self):
            return self._fade.type
        def __set__(self, uint8_t x):
            self._fade.type = x
