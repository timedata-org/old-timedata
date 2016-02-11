cdef extern from "fcolor/ColorName.h" namespace "fcolor":
    string rgbToName(FColor color)
    bool nameToRgb(string name, FColor* color)
