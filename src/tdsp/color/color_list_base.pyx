cdef extern from "<tdsp/color/colorList_inl.h>" namespace "tdsp":
    cppclass ColorList:
        Color& operator[](size_t)
        size_t size()
        void resize(size_t)
        void clear();
        bool fixKey(int& key)
        void setColor(size_t, float r, float g, float b)
        bool getColor(size_t , float r, float g, float b)
