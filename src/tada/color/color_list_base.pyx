cdef extern from "<tada/color/colorList_inl.h>" namespace "tada":
    cppclass ColorVector:
        ColorS& operator[](size_t)
        ColorS& back()
        size_t size()
        void resize(size_t)
        void clear();
        bool fixKey(int& key)
        void setColor(size_t, float r, float g, float b)
        bool getColor(size_t, float r, float g, float b)
        size_t getSizeOf()
        void push_back(ColorS&)

    void appendInto(ColorVector&, ColorVector& out)
    void duplicateInto(int, ColorVector&)
    size_t count(ColorVector&, ColorS&)
    int indexOf(ColorVector&, ColorS&)
    void insertBefore(ColorVector&, int, ColorS&)
    bool popAt(ColorVector&, int key, ColorS&)
    void sortColors(ColorVector&)

    void reverse(ColorVector&)
    void clearInto(ColorVector&)
    string toString(ColorVector&)
    string toString(ColorVector&, Base)
    ColorVector sliceVector(ColorVector&, int begin, int end, int step)
    int compareContainers(ColorVector&, ColorVector&)
    bool sliceIntoVector(ColorVector& _in, ColorVector& out,
                         int begin, int end, int step)

    ColorS maxColor(ColorVector&)
    ColorS minColor(ColorVector&)

    void rotate(ColorVector&, int positions)

    void absInto(ColorVector&)
    void ceilInto(ColorVector&)
    void floorInto(ColorVector&)
    void invertColor(ColorVector&)
    void negateColor(ColorVector&)
    void truncColor(ColorVector&)
    void roundColor(ColorVector&, uint digits)

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

    float distance(ColorVector&, ColorVector&)
    float distance2(ColorVector&, ColorVector&)

cdef extern from "<tada/color/hsv_inl.h>" namespace "tada":
    void hsvToRgbInto(ColorVector&, Base)
    void rgbToHsvInto(ColorVector&, Base)

cdef extern from "<tada/color/spread.h>" namespace "tada":
    ColorVector fillSpread(ColorS& c1, ColorS& c2, size_t size)
    void spreadAppend(ColorVector&, size_t size, ColorS&)
