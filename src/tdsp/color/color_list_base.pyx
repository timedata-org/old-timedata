cdef extern from "<tdsp/color/colorList_inl.h>" namespace "tdsp":
    cppclass ColorList:
        Color& operator[](size_t)
        size_t size()
        void resize(size_t)
        void clear();
        bool fixKey(int& key)
        void setColor(size_t, float r, float g, float b)
        bool getColor(size_t , float r, float g, float b)
        size_t getSizeOf()

    ColorList duplicate(ColorList&, int)
    void reverse(ColorList&)
    string toString(ColorList&)
    string toString(ColorList&, Base)
    ColorList sliceVector(ColorList&, int begin, int end, int step)
    int compareContainers(ColorList&, ColorList&)
    bool sliceIntoVector(ColorList& _in, ColorList& out,
                         int begin, int end, int step)

    void rotate(ColorList&, int positions)

    void absColor(ColorList&)
    void negateColor(ColorList&)
    void invertColor(ColorList&)

    void addInto(float f, ColorList& out)
    void addInto(ColorList&, ColorList& out)

    void divideInto(float f, ColorList& out)
    void divideInto(ColorList&, ColorList& out)

    void minInto(float f, ColorList& out)
    void minInto(ColorList&, ColorList& out)

    void maxInto(float f, ColorList& out)
    void maxInto(ColorList&, ColorList& out)

    void multiplyInto(float f, ColorList& out)
    void multiplyInto(ColorList&, ColorList& out)

    void powInto(float f, ColorList& out)
    void powInto(ColorList&, ColorList& out)

    void rdivideInto(float f, ColorList& out)
    void rdivideInto(ColorList&, ColorList& out)

    void rpowInto(float f, ColorList& out)
    void rpowInto(ColorList&, ColorList& out)

    void rsubtractInto(float f, ColorList& out)
    void rsubtractInto(ColorList&, ColorList& out)

    void subtractInto(float f, ColorList& out)
    void subtractInto(ColorList&, ColorList& out)

    void addOver(ColorList& x, ColorList& y, ColorList&)
    void addOver(float x, ColorList& y, ColorList&)
    void addOver(ColorList& x, float y, ColorList&)

    void divOver(ColorList& x, ColorList& y, ColorList&)
    void divOver(float x, ColorList& y, ColorList&)
    void divOver(ColorList& x, float y, ColorList&)

    void mulOver(ColorList& x, ColorList& y, ColorList&)
    void mulOver(float x, ColorList& y, ColorList&)
    void mulOver(ColorList& x, float y, ColorList&)

    void powOver(ColorList& x, ColorList& y, ColorList&)
    void powOver(float x, ColorList& y, ColorList&)
    void powOver(ColorList& x, float y, ColorList&)

    void subOver(ColorList& x, ColorList& y, ColorList&)
    void subOver(float x, ColorList& y, ColorList&)
    void subOver(ColorList& x, float y, ColorList&)
