# include "_operation.pyx"

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp":
    ctypedef vector[Color] ColorList

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp::operation":
    cdef cppclass Unary:
        pass

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp::operation::Unary":
    cdef Unary ABS
    cdef Unary CLEAR
    cdef Unary INVERT
    cdef Unary NEGATE

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp::operation":
    cdef cppclass Binary:
        pass

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp::operation::Binary":
    cdef Binary ADD
    cdef Binary DIV
    cdef Binary MAX
    cdef Binary MIN
    cdef Binary MUL
    cdef Binary POW
    cdef Binary SUB

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp::operation":
    cdef cppclass Side:
        pass

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp::operation::Side":
    cdef Side LEFT
    cdef Side RIGHT

cdef extern from "<tdsp/color/operation.h>" namespace "tdsp::operation":
    void run(Unary, ColorList& out)
    void run[X](Binary, Side, X, ColorList& out)
    void run[X, Y](Binary, Side, X, Y, ColorList& out)
