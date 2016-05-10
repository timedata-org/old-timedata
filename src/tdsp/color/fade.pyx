# Automatically generated on 2016-05-10T00:07:09.680418
# by https://github.com/rec/make_pyx/make_pyx.py

cdef extern from "<tdsp/color/fade.h>" namespace "tdsp":
    struct Fade:
        float begin, end
        float speed
        uint8_t type

    void clear(Fade&)


cdef class _Fade(_Wrapper):
    cdef Fade _fade;

    def __cinit__(self):
        clear(self._fade)

    def clear(self):
        clear(self._fade)

    def __str__(self):
        return '(begin=%s, end=%s, speed=%s, type=%s)' % (
            self.begin, self.end, self.speed, self.type)

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

    property speed:
        def __get__(self):
            return self._fade.speed
        def __set__(self, float x):
            self._fade.speed = x

    property type:
        def __get__(self):
            return self._fade.type
        def __set__(self, uint8_t x):
            self._fade.type = x
