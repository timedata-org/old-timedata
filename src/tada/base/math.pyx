cdef extern from "<tada/base/math.h>" namespace "tada":
    void clearStruct[T](T&)
    float divFixed(float, float)
    float powFixed(float, float)
