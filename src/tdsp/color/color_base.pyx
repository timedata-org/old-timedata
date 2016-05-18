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

    void minInto(ColorS&, ColorS&);
    void maxInto(ColorS&, ColorS&);

    float invert(float, float)
    float normalize(float, float)
    ColorS rotate(ColorS, int)
    bool stringToColor(const char*, ColorS&, Base)
    string colorToString(ColorS&, Base)
    bool cmpToRichcmp(float cmp, int richcmp)
    vector[string] colorNames()

cdef extern from "<tdsp/color/hsv.h>" namespace "tdsp":
    ColorS hsvToRgb(ColorS, Base)
    ColorS rgbToHsv(ColorS, Base)
