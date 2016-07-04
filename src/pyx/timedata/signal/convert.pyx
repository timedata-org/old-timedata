cdef extern from "<timedata/signal/convert.h>" namespace "timedata":
    uint64_t referenceToInteger[T](T&)
    bool convertModel[T](uint64_t pointer, string model, T&)
