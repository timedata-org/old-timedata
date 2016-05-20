cdef extern from "<tdsp/color/colorList_inl.h>" namespace "tdsp":
    cppclass ColorVector:
        ColorS& operator[](size_t)
        size_t size()
        void resize(size_t)
        void clear();
        bool fixKey(int& key)
        void setColor(size_t, float r, float g, float b)
        bool getColor(size_t , float r, float g, float b)
        size_t getSizeOf()

    ColorVector duplicate(ColorVector&, int)
    void reverse(ColorVector&)
    string toString(ColorVector&)
    string toString(ColorVector&, Base)
    ColorVector sliceVector(ColorVector&, int begin, int end, int step)
    int compareContainers(ColorVector&, ColorVector&)
    bool sliceIntoVector(ColorVector& _in, ColorVector& out,
                         int begin, int end, int step)

    void rotate(ColorVector&, int positions)

    void absColor(ColorVector&)
    void ceilColor(ColorVector&)
    void floorColor(ColorVector&)
    void invertColor(ColorVector&)
    void negateColor(ColorVector&)
    void roundColor(ColorVector&)
    void truncColor(ColorVector&)

    void addInto(float f, ColorVector& out)
    void addInto(ColorVector&, ColorVector& out)

    void divideInto(float f, ColorVector& out)
    void divideInto(ColorVector&, ColorVector& out)

    void minInto(float f, ColorVector& out)
    void minInto(ColorVector&, ColorVector& out)

    void maxInto(float f, ColorVector& out)
    void maxInto(ColorVector&, ColorVector& out)

    void multiplyInto(float f, ColorVector& out)
    void multiplyInto(ColorVector&, ColorVector& out)

    void powInto(float f, ColorVector& out)
    void powInto(ColorVector&, ColorVector& out)

    void rdivideInto(float f, ColorVector& out)
    void rdivideInto(ColorVector&, ColorVector& out)

    void rpowInto(float f, ColorVector& out)
    void rpowInto(ColorVector&, ColorVector& out)

    void rsubtractInto(float f, ColorVector& out)
    void rsubtractInto(ColorVector&, ColorVector& out)

    void subtractInto(float f, ColorVector& out)
    void subtractInto(ColorVector&, ColorVector& out)

    void addOver(ColorVector& x, ColorVector& y, ColorVector&)
    void addOver(float x, ColorVector& y, ColorVector&)
    void addOver(ColorVector& x, float y, ColorVector&)

    void divOver(ColorVector& x, ColorVector& y, ColorVector&)
    void divOver(float x, ColorVector& y, ColorVector&)
    void divOver(ColorVector& x, float y, ColorVector&)

    void mulOver(ColorVector& x, ColorVector& y, ColorVector&)
    void mulOver(float x, ColorVector& y, ColorVector&)
    void mulOver(ColorVector& x, float y, ColorVector&)

    void powOver(ColorVector& x, ColorVector& y, ColorVector&)
    void powOver(float x, ColorVector& y, ColorVector&)
    void powOver(ColorVector& x, float y, ColorVector&)

    void subOver(ColorVector& x, ColorVector& y, ColorVector&)
    void subOver(float x, ColorVector& y, ColorVector&)
    void subOver(ColorVector& x, float y, ColorVector&)


cdef extern from "<tdsp/color/hsv_inl.h>" namespace "tdsp":
    void hsvToRgbInto(ColorVector&, Base)
    void rgbToHsvInto(ColorVector&, Base)

cdef extern from "<tdsp/color/spread.h>" namespace "tdsp":
    ColorVector fillSpread(ColorS& c1, ColorS& c2, size_t size);
