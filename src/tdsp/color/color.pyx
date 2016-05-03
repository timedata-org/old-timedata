cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp":
    cdef cppclass RGB:
        pass

    cdef cppclass Sample[T]:
        float& at(int)

    bool toColor(const char*, Sample[RGB])
    string colorToString(float r, float g, float b)
    bool cmpToRichcmp(float cmp, int richcmp)


cdef class Color:
    cdef float red
    cdef float green
    cdef float blue

    def __cinit__(self, float red=0, float green=0, float blue=0):
        self.red = red
        self.green = green
        self.blue = blue

    @property
    def red(self):
        return self.red

    @property
    def green(self):
        return self.green

    @property
    def blue(self):
        return self.blue

    def __getitem__(self, int key):
        if key == 0:
            return self.red
        if key == 1:
            return self.green
        if key == 2:
            return self.blue
        raise IndexError('Color index out of range')

    def __abs__(self): pass

    def __add__(self, other): pass

    def __div__(self, other): pass

    def __divmod__(self, other): pass

    def __floordiv__(self, other): pass

    def __invert__(self): pass

    def __len__(self):
        return 3

    def __mod__(self, other): pass

    def __mul__(self, other): pass

    def __neg__(self): pass

    def __pos__(self): pass

    def __pow__(self, other, modulus): pass

    def __radd__(self, other): pass

    def __repr__(self):
        cl = self.__class__
        return '%s.%s(%s)' % (cl.__module__, cl.__name__, str(self))

    def __rdiv__(self, other): pass

    def __rdivmod__(self, other): pass

    def __rfloordiv__(self, other): pass

    def __richcmp__(Color self, Color c, int cmp):
        return cmpToRichcmp((self.red - c.red) or (self.green - c.green) or
                            (self.blue - c.blue), cmp)

    def __rmod__(self, other): pass

    def __rmul__(self, other): pass

    def __round__(self, n): pass

    def __rpow__(self, other, modulus): pass

    def __rsub__(self, other): pass

    def __str__(self):
        return colorToString(self.red, self.green, self.blue).decode('ascii')

    def __sub__(self, other): pass

    @staticmethod
    def make(x):
        if not isinstance(x, str):
            return Color(*x)

        cdef Sample[RGB] frame

        if toColor(x, frame):
            return Color(frame.at(0), frame.at(1), frame.at(2))
        raise ValueError("Can't understand color %s" % x)
