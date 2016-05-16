cdef extern from "<tdsp/base/math.h>" namespace "tdsp":
    void clearStruct[T](T&)
    float divFixed(float, float)
    float powFixed(float, float)
