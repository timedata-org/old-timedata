# Automatically generated on 2016-05-10T18:55:26.594135
# by https://github.com/rec/make_pyx/make_pyx.py

cdef extern from "<tdsp/color/fade.h>" namespace "tdsp::Fade":
    cdef cppclass Type:
        pass

cdef extern from "<tdsp/color/fade.h>" namespace "tdsp::Fade::Type":
    cdef Type linear
    cdef Type sqr
    cdef Type sqrt
    cdef Type size

cdef extern from "<tdsp/color/fade.h>" namespace "tdsp":
    struct Fade:
        float begin, end, fader
        Type type

    void clear(Fade&)


cdef class _Fade(_Wrapper):
    cdef Fade thisptr;

    TYPE_NAMES = 'linear', 'sqr', 'sqrt', 'size'

    def __cinit__(self):
        clear(self.thisptr)

    def clear(self):
        clear(self.thisptr)

    def __str__(self):
        return '(begin=%s, end=%s, fader=%s, type=%s)' % (
            self.begin, self.end, self.fader, self.type)

    property begin:
        def __get__(self):
            return self.thisptr.begin
        def __set__(self, float x):
            self.thisptr.begin = x

    property end:
        def __get__(self):
            return self.thisptr.end
        def __set__(self, float x):
            self.thisptr.end = x

    property fader:
        def __get__(self):
            return self.thisptr.fader
        def __set__(self, float x):
            self.thisptr.fader = x

    property type:
        def __get__(self):
            return self.TYPE_NAMES[<int> self.thisptr.type]
        def __set__(self, string x):
            cdef uint8_t i
            i = self.TYPE_NAMES.index(x)
            self.thisptr.type = <Type>(i)
