import math, numbers

cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp":
    cdef cppclass Base:
        pass

cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp::Base":
    cdef Base normal
    cdef Base integer


cdef extern from "<tdsp/color/names_inl.h>" namespace "tdsp":
    cdef cppclass ColorS

    cdef cppclass Color:
        Color()
        Color(ColorS&)
        float& at(int)

    cdef cppclass ColorS:
        float red, green, blue

        ColorS()
        ColorS(float, float, float)
        ColorS(Color&)

    float invert(float, float)
    float normalize(float, float)
    void rotate(Color&, int)
    bool stringToColor(const char*, Color, Base)
    string colorToString(ColorS&, Base)
    bool cmpToRichcmp(float cmp, int richcmp)
    Color makeColor(float r, float g, float b)
    vector[string] colorNames()

cdef extern from "<tdsp/color/hsv.h>" namespace "tdsp":
    Color hsvToRgb(Color, Base)
    Color rgbToHsv(Color, Base)
    Color hsvToRgb(Color)
    Color rgbToHsv(Color)
    ColorS hsvToRgb(ColorS, Base)
    ColorS rgbToHsv(ColorS, Base)
    ColorS hsvToRgb(ColorS)
    ColorS rgbToHsv(ColorS)


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
    cdef ColorS color

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
            self.color.red = self.color.green = self.color.blue = 0
            return

        if len(args) == 1:
            args = args[0]
            if isinstance(args, numbers.Number):
                self.color.red = self.color.green = self.color.blue = args
                return

            if isinstance(args, str):
                if not stringToColor(args, frame, self._base()):
                    raise ValueError("Can't understand color %s" % args)
                self.color.red = frame.at(0)
                self.color.green = frame.at(1)
                self.color.blue = frame.at(2)
                return

        if len(args) == 3:
            self.color.red, self.color.green, self.color.blue = args
        else:
            raise ValueError("Can't understand color %s" % args)

    @property
    def red(self):
        return self.color.red

    @property
    def green(self):
        return self.color.green

    @property
    def blue(self):
        return self.color.blue

    @property
    def ratio(_Color self):
        """Return the maximum ratio for this color range:  1.0 for Color
           and 255.0 for Color256."""
        return self._ratio()

    def rgb_to_hsv(_Color self):
        """Return a new color converting RGB to HSV."""
        cdef ColorS c
        c = rgbToHsv(self.color, self._base());
        return self.__class__(c.red, c.green, c.blue)

    def hsv_to_rgb(_Color self):
        """Return a new color converting RGB to HSV."""
        cdef ColorS c
        c = hsvToRgb(self.color, self._base());
        return self.__class__(c.red, c.green, c.blue)

    def normalized(_Color self):
        """Return a color normalized into this color range."""
        return self.__class__(self._norm(self.color.red),
                              self._norm(self.color.green),
                              self._norm(self.color.blue))

    def rotated(_Color self, int positions):
        """Return a color with the components rotated."""
        cdef Color c
        c = Color(self.color)
        rotate(c, positions)
        return self.__class__(c.at(0), c.at(1), c.at(2))

    def __getitem__(_Color self, object key):
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

    def __abs__(_Color self):
        return self.__class__(abs(self.color.red),
                              abs(self.color.green),
                              abs(self.color.blue))

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

    def __repr__(self):
        return '%s(%s)' % (self.class_name, str(self))

    def __richcmp__(self, object c, int cmp):
        return cmpToRichcmp((self.red - c.red) or
                            (self.green - c.green) or
                            (self.blue - c.blue), cmp)

    def __round__(_Color self, n):
        return self.__class__(round(self.color.red, n),
                              round(self.color.green, n),
                              round(self.color.blue, n))

    def __str__(_Color self):
        return colorToString(self.color, self._base()).decode('ascii')

    def __sizeof__(self):
        return 12  # 3 4-byte floats.

    def __sub__(self, c):
        c = self.__class__(c)
        return self.__class__(self.red - c.red,
                              self.green - c.green,
                              self.blue - c.blue)

    def __trunc__(_Color self):
        return self.__class__(math.trunc(self.color.red),
                              math.trunc(self.color.green),
                              math.trunc(self.color.blue))

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
