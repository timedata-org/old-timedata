include "_operation.pyx"

cdef extern from "<tdsp/color/operation_inl.h>" namespace "tdsp":
    ctypedef vector[Color] ColorList

    void run(Unary, ColorList& out);

    void runLeft(Binary, float, ColorList& out);
    void runLeft(Binary, ColorList&, ColorList& out);

    void runRight(Binary, float, ColorList& out);
    void runRight(Binary, ColorList&, ColorList& out);
