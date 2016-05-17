import math, numbers

cdef class _Color256:
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

    cdef float _norm(self, float x):
        return normalize(x, 255.0)

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
                if not stringToColor(args, frame, integer):
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
    def ratio(_Color256 self):
        """Return the maximum ratio for this color range:  1.0 for Color
           and 255.0 for Color256."""
        return 255.0

    def rgb_to_hsv(_Color256 self):
        """Return a new color converting RGB to HSV."""
        cdef ColorS c
        c = rgbToHsv(self.color, integer);
        return _Color256(c.red, c.green, c.blue)

    def hsv_to_rgb(_Color256 self):
        """Return a new color converting RGB to HSV."""
        cdef ColorS c
        c = hsvToRgb(self.color, integer);
        return _Color256(c.red, c.green, c.blue)

    def normalized(_Color256 self):
        """Return a color normalized into this color range."""
        return _Color256(self._norm(self.color.red),
                              self._norm(self.color.green),
                              self._norm(self.color.blue))

    def rotated(_Color256 self, int positions):
        """Return a color with the components rotated."""
        cdef Color c
        c = Color(self.color)
        rotate(c, positions)
        return _Color256(c.at(0), c.at(1), c.at(2))

    def __getitem__(_Color256 self, object key):
        if isinstance(key, slice):
            r = tuple(self[i] for i in range(*key.indices(len(self))))
            return _Color256(*r) if len(r) == 3 else r

        if key == 0 or key == -3:
            return self.color.red
        if key == 1 or key == -2:
            return self.color.green
        if key == 2 or key == -1:
            return self.color.blue
        raise IndexError('Color index out of range')

    # Operations where self is *not* necessarily a color!
    # This can happen if "self" appear on the right in an operation.
    # So all of these are wrong in fact.  :-D
    def __add__(self, c):
        c = _Color256(c)
        return _Color256(self.red + c.red,
                              self.green + c.green,
                              self.blue + c.blue)

    def __truediv__(self, c):
        c = _Color256(c)
        return _Color256(divFixed(self.red, c.red),
                              divFixed(self.green, c.green),
                              divFixed(self.blue, c.blue))

    def __divmod__(self, c):
        c = _Color256(c)
        dr, mr = divmod(self.red, c.red)
        dg, mg = divmod(self.green, c.green)
        db, mb = divmod(self.blue, c.blue)
        return _Color256(dr, dg, db), _Color256(mr, mg, mb)

    def __mod__(self, c):
        c = _Color256(c)
        return _Color256(self.red % c.red,
                              self.green % c.green,
                              self.blue % c.blue)

    def __mul__(self, c):
        c = _Color256(c)
        return _Color256(self.red * c.red,
                              self.green * c.green,
                              self.blue * c.blue)

    def __pow__(self, c, mod):
        c = _Color256(c)
        if mod is None:
            return _Color256(powFixed(self.red, c.red),
                                  powFixed(self.green, c.green),
                                  powFixed(self.blue, c.blue))

        m = _Color256(mod)
        return _Color256(pow(self.red, c.red, m.red),
                              pow(self.green, c.green, m.green),
                              pow(self.blue, c.blue, m.blue))

    def __sub__(self, c):
        c = _Color256(c)
        return _Color256(self.red - c.red,
                              self.green - c.green,
                              self.blue - c.blue)

    def __abs__(_Color256 self):
        return _Color256(abs(self.color.red),
                              abs(self.color.green),
                              abs(self.color.blue))

    def __ceil__(_Color256 self):
        return _Color256(math.ceil(self.color.red),
                              math.ceil(self.color.green),
                              math.ceil(self.color.blue))

    def __floor__(_Color256 self):
        return _Color256(math.floor(self.color.red),
                              math.floor(self.color.green),
                              math.floor(self.color.blue))

    def __invert__(_Color256 self):
        """Return the complementary color."""
        cdef float i
        i = 255 if (<int> integer == 1) else 1
        return _Color256(invert(self.red, i),
                            invert(self.green, i),
                            invert(self.blue, i))

    def __len__(_Color256 self):
        return 3

    def __neg__(_Color256 self):
        return _Color256(-self.red, -self.green, -self.blue)

    def __repr__(_Color256 self):
        return '_Color256(%s)' % str(self)

    def __richcmp__(_Color256 self, _Color256 c, int cmp):
        return cmpToRichcmp((self.red - c.red) or
                            (self.green - c.green) or
                            (self.blue - c.blue), cmp)

    def __round__(_Color256 self, n):
        return _Color256(round(self.color.red, n),
                              round(self.color.green, n),
                              round(self.color.blue, n))

    def __str__(_Color256 self):
        return colorToString(self.color, integer).decode('ascii')

    def __sizeof__(_Color256 self):
        return 12  # 3 4-byte floats.

    def __trunc__(_Color256 self):
        return _Color256(math.trunc(self.color.red),
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
