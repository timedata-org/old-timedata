# Automatically generated on 2016-05-10T19:23:23.752164
# by https://github.com/rec/make_pyx/make_pyx.py

cdef extern from "<tdsp/signal/stripe.h>" namespace "tdsp":
    struct Stripe:
        int begin, skip
        size_t repeats
        bool reflect


cdef class _Stripe(_Wrapper):
    cdef Stripe thisptr;

    def __cinit__(self):
        clearStruct(self.thisptr)

    def clear(self):
        clearStruct(self.thisptr)

    def __str__(self):
        return '(begin=%s, skip=%s, repeats=%s, reflect=%s)' % (
            self.begin, self.skip, self.repeats, self.reflect)

    property begin:
        def __get__(self):
            return self.thisptr.begin
        def __set__(self, int x):
            self.thisptr.begin = x

    property skip:
        def __get__(self):
            return self.thisptr.skip
        def __set__(self, int x):
            self.thisptr.skip = x

    property repeats:
        def __get__(self):
            return self.thisptr.repeats
        def __set__(self, size_t x):
            self.thisptr.repeats = x

    property reflect:
        def __get__(self):
            return self.thisptr.reflect
        def __set__(self, bool x):
            self.thisptr.reflect = x
