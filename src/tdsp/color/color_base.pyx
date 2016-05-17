import math, numbers

cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp":
    cdef cppclass Base:
        pass

cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp::Base":
    cdef Base normal
    cdef Base integer


cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp":
    cdef cppclass ColorS

    cdef cppclass Color:
        Color()
        Color(ColorS&)
        float& at(int)

    cdef cppclass ColorS:
        float red, green, blue

        ColorS()
        ColorS(float, float, float)
        ColorS(Color&)

    float invert(float, float)
    float normalize(float, float)
    void rotate(Color&, int)
    bool stringToColor(const char*, Color, Base)
    string colorToString(ColorS&, Base)
    bool cmpToRichcmp(float cmp, int richcmp)
    Color makeColor(float r, float g, float b)
    vector[string] colorNames()

cdef extern from "<tdsp/color/hsv.h>" namespace "tdsp":
    Color hsvToRgb(Color, Base)
    Color rgbToHsv(Color, Base)
    Color hsvToRgb(Color)
    Color rgbToHsv(Color)
    ColorS hsvToRgb(ColorS, Base)
    ColorS rgbToHsv(ColorS, Base)
    ColorS hsvToRgb(ColorS)
    ColorS rgbToHsv(ColorS)
