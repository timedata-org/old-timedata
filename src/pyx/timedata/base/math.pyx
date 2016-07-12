cdef extern from "<timedata/base/math.h>" namespace "timedata":
    void clearStruct[T](T&)

    float divPython(float, float)
    float powPython(float, float)
    float modPython(float, float)
