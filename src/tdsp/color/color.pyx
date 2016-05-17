import math, numbers

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
    float normalize(float, float)
    void rotate(Color&, int)
    bool stringToColor(const char*, Color, Base)
    string colorToString(float r, float g, float b, Base)
    bool cmpToRichcmp(float cmp, int richcmp)
    Color makeColor(float r, float g, float b)
    vector[string] colorNames()

cdef extern from "<tdsp/color/hsv.h>" namespace "tdsp":
    Color hsvToRgb(Color, Base)
    Color rgbToHsv(Color, Base)
    Color hsvToRgb(Color)
    Color rgbToHsv(Color)


cdef class _Color:
    """A Color is an immutable RGB floating point color.

       A Color looks very much like a Python tuple with three floating point
       numbers, with the big exception that operators like + and * perform
       arithmetic, not list-style operations.

       The constructor for Color takes a triple of numbers but also strings
       representing human-readable color names like "red" and "green".

       Color supports the operations +, -, *, /, %, pow, and ~ (which means
       "take the complementary color").

       Colors are very lightweight - about half the size of a corresponding
       Python tuple and more than twice as fast to create and copy.  Colors are
       also immutable - all operations on Colors have to create a new Color.

       There are two models of color.  The base class Color is normalized so
       that the standard range for output signals - that is, outout color
       components - is [0.0, 1.0].  As always, intermediate signals can be
       greater than 1 or even negative.

       The derived class Color256 has a standard output range of [0, 255] to
    """
    cdef float red
    cdef float green
    cdef float blue

    class_name = 'Color'

    cdef Base _base(self):
        return normal

    cdef float _ratio(self):
        return 255.0 if (<int> self._base()) else 1.0

    cdef float _norm(self, float x):
        return normalize(x, self._ratio())

    def __init__(self, *args):
        cdef Color frame
        if not args:
            self.red = self.green = self.blue = 0
            return

        if len(args) == 1:
            args = args[0]
            if isinstance(args, numbers.Number):
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
    def ratio(self):
        """Return the maximum ratio for this color range:  1.0 for Color
           and 255.0 for Color256."""
        return self._ratio()

    def rgb_to_hsv(self):
        """Convert this RGB color to an HSV."""
        c = makeColor(self.red, self.green, self.blue)
        c = rgbToHsv(c, self._base());
        return self.__class__(c.at(0), c.at(1), c.at(2))

    def hsv_to_rgb(self):
        """Convert this HSV color to an RGB."""
        c = makeColor(self.red, self.green, self.blue)
        c = hsvToRgb(c, self._base());
        return self.__class__(c.at(0), c.at(1), c.at(2))

    def normalized(self):
        """Return a color normalized into this color range."""
        return self.__class__(self._norm(self.red),
                              self._norm(self.green),
                              self._norm(self.blue))

    def rotated(self, int positions):
        """Return a color with the components rotated."""
        cdef Color c
        c = makeColor(self.red, self.green, self.blue)
        rotate(c, positions)
        return self.__class__(c.at(0), c.at(1), c.at(2))

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

    def __ceil__(self):
        return self.__class__(math.ceil(self.red),
                              math.ceil(self.green),
                              math.ceil(self.blue))

    def __truediv__(self, c):
        c = self.__class__(c)
        return self.__class__(divFixed(self.red, c.red),
                              divFixed(self.green, c.green),
                              divFixed(self.blue, c.blue))

    def __divmod__(self, c):
        c = self.__class__(c)
        dr, mr = divmod(self.red, c.red)
        dg, mg = divmod(self.green, c.green)
        db, mb = divmod(self.blue, c.blue)
        return self.__class__(dr, dg, db), self.__class__(mr, mg, mb)

    def __floor__(self):
        return self.__class__(math.floor(self.red),
                              math.floor(self.green),
                              math.floor(self.blue))

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
            return self.__class__(powFixed(self.red, c.red),
                                  powFixed(self.green, c.green),
                                  powFixed(self.blue, c.blue))

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
        return self.__class__(divFixed(c.red, self.red),
                              divFixed(c.green, self.green),
                              divFixed(c.blue, self.blue))

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
            return self.__class__(powFixed(c.red, self.red),
                                  powFixed(c.green, self.green),
                                  powFixed(c.blue, self.blue))

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

    def __sizeof__(self):
        return 12  # 3 4-byte floats.

    def __sub__(self, c):
        c = self.__class__(c)
        return self.__class__(self.red - c.red,
                              self.green - c.green,
                              self.blue - c.blue)

    def __trunc__(self):
        return self.__class__(math.trunc(self.red),
                              math.trunc(self.green),
                              math.trunc(self.blue))

    @staticmethod
    def names():
        cdef vector[string] names
        result = []
        names = colorNames()
        for i in names:
            result.append(i.decode('ascii'))
        return result


cdef class _Color256(_Color):
    class_name = 'Color256'

    cdef Base _base(self):
        return integer
