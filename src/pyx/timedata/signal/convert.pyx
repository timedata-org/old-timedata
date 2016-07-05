cdef extern from "<timedata/signal/convert.h>" namespace "timedata":
    ctypedef uint64_t PointerAsInt

    cdef PointerAsInt referenceToInteger[T](T&)

    string className[T]()
