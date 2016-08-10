cdef extern from "<timedata/signal/convert_inl.h>" namespace "timedata::converter":
    ctypedef uint64_t PointerAsInt

    cdef PointerAsInt referenceToInteger[T](T&)

    string loadConverter[T]()
    bool convertSampleCython[T](PointerAsInt input, string model, T& out)

cdef extern from "<timedata/color/rgbAdaptor.h>" namespace "timedata::color_list":
    cdef cppclass RGBIndexer:
        pass

    RGBIndexer getIndexer[T](T& colors)

cdef class Indexer:
   cpdef RGBIndexer cdata
