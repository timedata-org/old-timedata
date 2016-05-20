import math, numbers

cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp":
    cdef cppclass Base:
        pass

cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp::Base":
    cdef Base normal
    cdef Base integer

cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp":
    cdef cppclass ColorS:
        float red, green, blue

        ColorS()
        ColorS(float, float, float)

    void minInto(ColorS&, ColorS&);
    void maxInto(ColorS&, ColorS&);

    float invert(float, float)
    float normalize(float, float)
    ColorS rotate(ColorS, int)
    bool stringToColor(const char*, ColorS&, Base)
    string colorToString(ColorS&, Base)
    bool cmpToRichcmp(float cmp, int richcmp)
    vector[string] colorNames()
    ColorS colorFromHex(uint32_t hex, Base base);
    uint32_t hexFromColor(ColorS&, Base base);
    float distance2(ColorS&, ColorS&)
    float distance(ColorS&, ColorS&)

cdef extern from "<tdsp/color/hsv.h>" namespace "tdsp":
    ColorS hsvToRgb(ColorS, Base)
    ColorS rgbToHsv(ColorS, Base)
