cdef extern from "<tdsp/color/stripe.h>" namespace "tdsp":
    struct Stripe:
        int begin, skip
        size_t repeats
        bool reflect


cdef class _Stripe:
    cdef Stripe _stripe;

    property begin:
        def __get__(self):            return self._stripe.begin
        def __set__(self, int x):     self._stripe.begin = x

    property skip:
        def __get__(self):            return self._stripe.skip
        def __set__(self, int x):     self._stripe.skip = x

    property repeats:
        def __get__(self):            return self._stripe.repeats
        def __set__(self, size_t x):  self._stripe.repeats = x

    property reflect:
        def __get__(self):            return self._stripe.reflect
        def __set__(self, bool x):    self._stripe.reflect = x


globals()['Stripe'] = _Stripe
