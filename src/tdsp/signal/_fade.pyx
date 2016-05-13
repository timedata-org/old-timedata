# Automatically generated on 2016-05-13T19:13:59.870813
# by https://github.com/rec/make_pyx/make_pyx.py
cdef extern from "<tdsp/signal/fade.h>" namespace "tdsp::Fade":
    cdef cppclass Type:
        pass

cdef extern from "<tdsp/signal/fade.h>" namespace "tdsp::Fade::Type":
    cdef Type linear
    cdef Type sqr
    cdef Type sqrt

cdef extern from "<tdsp/signal/fade.h>" namespace "tdsp":
    struct Fade:
        float begin, end, fader
        Type type

cdef class _Fade(_Wrapper):
    cdef Fade _instance;

    TYPE_NAMES = 'linear', 'sqr', 'sqrt'

    def __cinit__(self):
        clearStruct(self._instance)

    def clear(self):
        clearStruct(self._instance)

    def __str__(self):
        return "(begin=%s, end=%s, fader=%s, type='%s')" % (
            self.begin, self.end, self.fader, self.type)

    property begin:
        def __get__(self):
            return self._instance.begin
        def __set__(self, float x):
            self._instance.begin = x

    property end:
        def __get__(self):
            return self._instance.end
        def __set__(self, float x):
            self._instance.end = x

    property fader:
        def __get__(self):
            return self._instance.fader
        def __set__(self, float x):
            self._instance.fader = x

    property type:
        def __get__(self):
            return self.TYPE_NAMES[<int> self._instance.type]
        def __set__(self, string x):
            cdef uint8_t i
            i = self.TYPE_NAMES.index(x)
            self._instance.type = <Type>(i)
