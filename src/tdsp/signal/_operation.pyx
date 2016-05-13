# Automatically generated on 2016-05-13T19:14:03.858595
# by https://github.com/rec/make_pyx/make_pyx.py
cdef extern from "<tdsp/signal/operation.h>" namespace "tdsp::Operation":
    cdef cppclass Unary:
        pass

cdef extern from "<tdsp/signal/operation.h>" namespace "tdsp::Operation::Unary":
    cdef Unary ABS
    cdef Unary CLEAR
    cdef Unary INVERT
    cdef Unary NEGATE

cdef extern from "<tdsp/signal/operation.h>" namespace "tdsp::Operation":
    cdef cppclass Commutative:
        pass

cdef extern from "<tdsp/signal/operation.h>" namespace "tdsp::Operation::Commutative":
    cdef Commutative ADD
    cdef Commutative MAX
    cdef Commutative MIN
    cdef Commutative MUL

cdef extern from "<tdsp/signal/operation.h>" namespace "tdsp::Operation":
    cdef cppclass NonCommutative:
        pass

cdef extern from "<tdsp/signal/operation.h>" namespace "tdsp::Operation::NonCommutative":
    cdef NonCommutative DIV
    cdef NonCommutative SUB
    cdef NonCommutative POW
