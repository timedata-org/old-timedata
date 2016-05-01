cdef extern from "tdsp/ColorName.h" namespace "tdsp":
    string rgbToName(FColor color)
    bool nameToRgb(string name, FColor* color)
