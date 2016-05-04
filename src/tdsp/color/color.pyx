cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp":
    cdef cppclass RGB:
        pass

    cdef cppclass Sample[T]:
        float& at(int)

    bool toColor(const char*, Sample[RGB])
    string colorToString(float r, float g, float b)
    bool cmpToRichcmp(float cmp, int richcmp)


cdef class _Color:
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

    @staticmethod
    def make(x):
        if isinstance(x, _Color):
            return x

        cdef Sample[RGB] frame
        try:
            if isinstance(x, str):
                if toColor(x, frame):
                    return _Color(frame.at(0), frame.at(1), frame.at(2))

            try:
                len(x)
            except:
                return _Color(x, x, x)
            if len(x) == 3:
                return _Color(*x)
            raise ValueError()

        except:
            raise ValueError("Can't understand color %s" % x)

    def __getitem__(self, int key):
        if key == 0:
            return self.red
        if key == 1:
            return self.green
        if key == 2:
            return self.blue
        raise IndexError('Color index out of range')

    def __abs__(self):
        return _Color(abs(self.red), abs(self.green), abs(self.blue))

    def __add__(self, c):
        c = _Color.make(c)
        return _Color(self.red + c.red, self.green + c.green, self.blue + c.blue)

    def __div__(self, c):
        c = _Color.make(c)
        return _Color(self.red / c.red, self.green / c.green, self.blue / c.blue)

    def __divmod__(self, c):
        c = _Color.make(c)
        dr, mr = divmod(self.red, c.red)
        dg, mg = divmod(self.green, c.green)
        db, mb = divmod(self.blue, c.blue)
        return _Color(dr, dg, db), _Color(mr, mg, mb)

    def __invert__(self):
        """Return the complementary color."""
        return _Color(1.0 - self.red, 1.0 - self.green, 1.0 - self.blue)

    def __len__(self):
        return 3

    def __mod__(self, c):
        c = _Color.make(c)
        return _Color(self.red % c.red, self.green % c.green, self.blue % c.blue)

    def __mul__(self, c):
        c = _Color.make(c)
        return _Color(self.red * c.red, self.green * c.green, self.blue * c.blue)

    def __neg__(self):
        return _Color(-self.red, -self.green, -self.blue)

    def __pow__(self, c, mod):
        c = _Color.make(c)
        if mod is None:
            return _Color(self.red ** c.red,
                         self.green ** c.green,
                         self.blue ** c.blue)

        m = _Color.make(mod)
        return _Color(pow(self.red, c.red, m.red),
                     pow(self.green, c.green, m.green),
                     pow(self.blue, c.blue, m.blue))

    def __radd__(self, c):
        c = _Color.make(c)
        return _Color(self.red + c.red, self.green + c.green, self.blue + c.blue)

    def __repr__(self):
        cl = self.__class__
        return '%s.%s(%s)' % (cl.__module__, cl.__name__, str(self))

    def __rdiv__(self, c):
        c = _Color.make(c)
        return _Color(c.red / self.red, c.green / self.green, c.blue / self.blue)

    def __rdivmod__(self, c):
        c = _Color.make(c)
        dr, mr = divmod(c.red, self.red)
        dg, mg = divmod(c.green, self.green)
        db, mb = divmod(c.blue, self.blue)
        return _Color(dr, dg, db), _Color(mr, mg, mb)

    def __richcmp__(_Color self, _Color c, int cmp):
        return cmpToRichcmp((self.red - c.red) or
                            (self.green - c.green) or
                            (self.blue - c.blue), cmp)

    def __rmod__(self, c):
        c = _Color.make(c)
        return _Color(c.red % self.red, c.green % self.green, c.blue % self.blue)

    def __rmul__(self, c):
        c = _Color.make(c)
        return _Color(c.red * self.red, c.green * self.green, c.blue * self.blue)

    def __round__(self, n):
        return _Color(round(self.red, n),
                     round(self.green, n),
                     round(self.blue, n))

    def __rpow__(self, c, mod):
        c = _Color.make(c)
        if mod is None:
            return _Color(c.red ** self.red,
                         c.green ** self.green,
                         c.blue ** self.blue)

        m = _Color.make(mod)
        return _Color(pow(c.red, self.red, m.red),
                     pow(c.green, self.green, m.green),
                     pow(c.blue, self.blue, m.blue))

    def __rsub__(self, c):
        c = _Color.make(c)
        return _Color(c.red - self.red, c.green - self.green, c.blue - self.blue)

    def __str__(self):
        return colorToString(self.red, self.green, self.blue).decode('ascii')

    def __sub__(self, c):
        c = _Color.make(c)
        return _Color(self.red - c.red, self.green - c.green, self.blue - c.blue)

Color = _Color
