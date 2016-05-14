# Automatically generated on 2016-05-14T15:42:56.467663
# by https://github.com/rec/make_pyx/make_pyx.py
cdef extern from "<tdsp/color/operation.h>" namespace "tdsp::Operation":
    cdef cppclass Unary:
        pass

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp::Operation::Unary":
    cdef Unary ABS
    cdef Unary CLEAR
    cdef Unary INVERT
    cdef Unary NEGATE

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp::Operation":
    cdef cppclass Binary:
        pass

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp::Operation::Binary":
    cdef Binary ADD
    cdef Binary DIV
    cdef Binary MAX
    cdef Binary MIN
    cdef Binary MUL
    cdef Binary POW
    cdef Binary SUB
