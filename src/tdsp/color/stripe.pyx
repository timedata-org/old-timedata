# Automatically generated on 2016-05-09T23:02:40.257282
# by https://github.com/rec/make_pyx/make_pyx.py

cdef extern from "<tdsp/color/stripe.h>" namespace "tdsp":
    struct Stripe:
        int begin, skip
        size_t repeats
        bool reflect


cdef class _Stripe(_Wrapper):
    cdef Stripe _stripe;

    def __cinit__(self):
        self._stripe = Stripe()

    def __str__(self):
        return '(begin=%s, skip=%s, repeats=%s, reflect=%s)' % (
            self.begin, self.skip, self.repeats, self.reflect)

    property begin:
        def __get__(self):
            return self._stripe.begin
        def __set__(self, int x):
            self._stripe.begin = x

    property skip:
        def __get__(self):
            return self._stripe.skip
        def __set__(self, int x):
            self._stripe.skip = x

    property repeats:
        def __get__(self):
            return self._stripe.repeats
        def __set__(self, size_t x):
            self._stripe.repeats = x

    property reflect:
        def __get__(self):
            return self._stripe.reflect
        def __set__(self, bool x):
            self._stripe.reflect = x
