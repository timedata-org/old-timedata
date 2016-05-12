from numbers import Number

cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp":
    cdef cppclass Base:
        pass

cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp::Base":
    cdef Base normal
    cdef Base integer


cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp":
    cdef cppclass Color:
        float& at(int)

    float invert(float, float)
    bool stringToColor(const char*, Color, Base)
    string colorToString(float r, float g, float b, Base)
    bool cmpToRichcmp(float cmp, int richcmp)
    Color makeColor(float r, float g, float b)


cdef class _Color:
    cdef float red
    cdef float green
    cdef float blue

    class_name = 'Color'

    cdef Base _base(self):
        return normal

    def __init__(self, *args):
        cdef Color frame
        if not args:
            self.red = self.green = self.blue = 0
            return

        if len(args) == 1:
            args = args[0]
            if isinstance(args, Number):
                self.red = self.green = self.blue = args
                return

            if isinstance(args, str):
                if not stringToColor(args, frame, self._base()):
                    raise ValueError("Can't understand color %s" % args)
                self.red = frame.at(0)
                self.green = frame.at(1)
                self.blue = frame.at(2)
                return

        if len(args) == 3:
            self.red, self.green, self.blue = args
        else:
            raise ValueError("Can't understand color %s" % args)

    @property
    def red(self):
        return self.red

    @property
    def green(self):
        return self.green

    @property
    def blue(self):
        return self.blue

    @property
    def base(self):
        return <int> self._base()

    def __getitem__(self, object key):
        if isinstance(key, slice):
            r = tuple(self[i] for i in range(*key.indices(len(self))))
            return self.__class__(*r) if len(r) == 3 else r

        if key == 0 or key == -3:
            return self.red
        if key == 1 or key == -2:
            return self.green
        if key == 2 or key == -1:
            return self.blue
        raise IndexError('Color index out of range')

    def __abs__(self):
        return self.__class__(abs(self.red), abs(self.green), abs(self.blue))

    def __add__(self, c):
        c = self.__class__(c)
        return self.__class__(self.red + c.red,
                      self.green + c.green,
                      self.blue + c.blue)

    def __truediv__(self, c):
        c = self.__class__(c)
        return self.__class__(self.red / c.red,
                      self.green / c.green,
                      self.blue / c.blue)

    def __divmod__(self, c):
        c = self.__class__(c)
        dr, mr = divmod(self.red, c.red)
        dg, mg = divmod(self.green, c.green)
        db, mb = divmod(self.blue, c.blue)
        return self.__class__(dr, dg, db), self.__class__(mr, mg, mb)

    def __invert__(self):
        """Return the complementary color."""
        cdef float i
        i = 255 if (<int> self._base() == 1) else 1
        return self.__class__(invert(self.red, i),
                      invert(self.green, i),
                      invert(self.blue, i))

    def __len__(self):
        return 3

    def __mod__(self, c):
        c = self.__class__(c)
        return self.__class__(self.red % c.red,
                      self.green % c.green,
                      self.blue % c.blue)

    def __mul__(self, c):
        c = self.__class__(c)
        return self.__class__(self.red * c.red,
                              self.green * c.green,
                              self.blue * c.blue)

    def __neg__(self):
        return self.__class__(-self.red, -self.green, -self.blue)

    def __pow__(self, c, mod):
        c = self.__class__(c)
        if mod is None:
            return self.__class__(self.red ** c.red,
                                  self.green ** c.green,
                                  self.blue ** c.blue)

        m = self.__class__(mod)
        return self.__class__(pow(self.red, c.red, m.red),
                              pow(self.green, c.green, m.green),
                              pow(self.blue, c.blue, m.blue))

    def __radd__(self, c):
        c = self.__class__(c)
        return self.__class__(self.red + c.red,
                      self.green + c.green,
                      self.blue + c.blue)

    def __repr__(self):
        return '%s(%s)' % (self.class_name, str(self))

    def __rdiv__(self, c):
        c = self.__class__(c)
        return self.__class__(c.red / self.red,
                      c.green / self.green,
                      c.blue / self.blue)

    def __rdivmod__(self, c):
        c = self.__class__(c)
        dr, mr = divmod(c.red, self.red)
        dg, mg = divmod(c.green, self.green)
        db, mb = divmod(c.blue, self.blue)
        return (self.__class__(dr, dg, db),
                self.__class__(mr, mg, mb))

    def __richcmp__(self, object c, int cmp):
        return cmpToRichcmp((self.red - c.red) or
                            (self.green - c.green) or
                            (self.blue - c.blue), cmp)

    def __rmod__(self, c):
        c = self.__class__(c)
        return self.__class__(c.red % self.red,
                              c.green % self.green,
                              c.blue % self.blue)

    def __rmul__(self, c):
        c = self.__class__(c)
        return self.__class__(c.red * self.red,
                              c.green * self.green,
                              c.blue * self.blue)

    def __round__(self, n):
        return self.__class__(round(self.red, n),
                              round(self.green, n),
                              round(self.blue, n))

    def __rpow__(self, c, mod):
        c = self.__class__(c)
        if mod is None:
            return self.__class__(c.red ** self.red,
                                  c.green ** self.green,
                                  c.blue ** self.blue)

        m = self.__class__(mod)
        return self.__class__(pow(c.red, self.red, m.red),
                              pow(c.green, self.green, m.green),
                              pow(c.blue, self.blue, m.blue))

    def __rsub__(self, c):
        c = self.__class__(c)
        return self.__class__(c.red - self.red,
                              c.green - self.green,
                              c.blue - self.blue)

    def __str__(self):
        return colorToString(self.red, self.green, self.blue, self._base()
                             ).decode('ascii')

    def __sub__(self, c):
        c = self.__class__(c)
        return self.__class__(self.red - c.red,
                              self.green - c.green,
                              self.blue - c.blue)


cdef class _Color256(_Color):
    class_name = 'Color256'

    cdef Base _base(self):
        return integer
