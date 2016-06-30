import math, numbers

cdef extern from "<timedata/color/names_inl.h>" namespace "timedata":
    cdef cppclass Base:
        pass

cdef extern from "<timedata/color/names_inl.h>" namespace "timedata::Base":
    cdef Base normal
    cdef Base integer

cdef extern from "<timedata/color/names_inl.h>" namespace "timedata":
    cdef cppclass OldColorS:
        float red, green, blue

        OldColorS()
        OldColorS(float, float, float)

    # These next operations might make sense with any time data.
    void minInto(OldColorS&, OldColorS&);
    void maxInto(OldColorS&, OldColorS&);

    float invert(float, float)
    float normalize(float, float)
    OldColorS rotate(OldColorS, int)
    bool cmpToRichcmp(float cmp, int richcmp)
    float distance2(OldColorS&, OldColorS&)
    float distance(OldColorS&, OldColorS&)
    float cmp(OldColorS&, OldColorS&)

    # Color-only operations
    bool stringToColor(const char*, OldColorS&, Base)
    string colorToString(OldColorS&, Base)
    vector[string] colorNames()
    OldColorS colorFromHex(uint32_t hex, Base base);
    uint32_t hexFromColor(OldColorS&, Base base);


cdef extern from "<timedata/color/hsv.h>" namespace "timedata":
    OldColorS hsvToRgb(OldColorS, Base)
    OldColorS rgbToHsv(OldColorS, Base)
