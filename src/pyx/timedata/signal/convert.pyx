cdef extern from "<timedata/signal/convert_inl.h>" namespace "timedata::converter":
    ctypedef uint64_t PointerAsInt

    cdef PointerAsInt referenceToInteger[T](T&)

    string loadConverter[T]()
    bool convertSamples[T](PointerAsInt input, string model, T& out)
