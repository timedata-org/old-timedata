cdef extern from "<tada/base/math.h>" namespace "tada":
    void clearStruct[T](T&)
    float divPython(float, float)
    float powPython(float, float)
    float modPython(float, float)
