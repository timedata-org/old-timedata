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

cdef extern from "<tdsp/color/operation_inl.h>" namespace "tdsp::operation":
    void runUnary(Unary, ColorList& out)

    void runInto(Binary, Side, float, ColorList& out)
    void runInto(Binary, Side, ColorList&, ColorList& out)

    void runTogether(Binary, Side, ColorList&, float, ColorList& out)
    void runTogether(Binary, Side, ColorList&, ColorList&, ColorList& out)
