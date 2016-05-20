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

    def __init__(self, *args):
        if not args:
            self.color.red = self.color.green = self.color.blue = 0
            return

        if len(args) == 1:
            args = args[0]
            if isinstance(args, numbers.Number):
                self.color.red = self.color.green = self.color.blue = args
                return

            if isinstance(args, str):
                if stringToColor(args, self.color, integer):
                    return
                raise ValueError("Can't understand color %s" % args)

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

    cpdef rgb_to_hsv(_Color256 self):
        """Return a new color converting RGB to HSV."""
        cdef ColorS c
        c = rgbToHsv(self.color, integer);
        return _Color256(c.red, c.green, c.blue)

    cpdef hsv_to_rgb(_Color256 self):
        """Return a new color converting RGB to HSV."""
        cdef ColorS c
        c = hsvToRgb(self.color, integer);
        return _Color256(c.red, c.green, c.blue)

    def limited(_Color256 self, *, min=None, max=None):
        """Return a new color limited to be not less than min (if given)
           and not greater than max (if given)."""
        cdef _Color256 c
        c = self[:]
        if min is not None:
            minInto(_make_Color256(min).color, c.color)
        if max is not None:
            maxInto(_make_Color256(max).color, c.color)
        return c

    cpdef distance(_Color256 self, _Color256 other):
        """Return the cartesian distance between this color and another."""
        return distance(self.color, other.color)

    cpdef distance2(_Color256 self, _Color256 other):
        """Return the square of the cartesian distance between this color and
           another - this is somewhat more efficient and often good enough."""
        return distance2(self.color, other.color)

    cpdef normalized(_Color256 self):
        """Return a color normalized into this color range."""
        return _Color256(normalize(self.color.red, 255.0),
                              normalize(self.color.green, 255.0),
                              normalize(self.color.blue, 255.0))

    cpdef rotated(_Color256 self, int positions):
        """Return a color with the components rotated."""
        cdef _Color256 c
        c = _Color256()
        c.color = rotate(self.color, positions)
        return c

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
        cdef ColorS x, y
        x = _make_Color256(self).color
        y = _make_Color256(c).color
        return _Color256(x.red + y.red, x.green + y.green, x.blue + y.blue)

    def __truediv__(self, c):
        cdef ColorS x, y
        x = _make_Color256(self).color
        y = _make_Color256(c).color
        return _Color256(divFixed(x.red, y.red),
                              divFixed(x.green, y.green),
                              divFixed(x.blue, y.blue))

    def __divmod__(self, c):
        cdef ColorS x, y
        cdef float dr, mr, dg, mg, db, mb

        x = _make_Color256(self).color
        y = _make_Color256(c).color

        dr, mr = divmod(x.red, y.red)
        dg, mg = divmod(x.green, y.green)
        db, mb = divmod(x.blue, y.blue)
        return _Color256(dr, dg, db), _Color256(mr, mg, mb)

    def __mod__(self, c):
        cdef ColorS x, y
        x = _make_Color256(self).color
        y = _make_Color256(c).color

        return _Color256(x.red % y.red, x.green % y.green, x.blue % y.blue)

    def __mul__(self, c):
        cdef ColorS x, y
        x = _make_Color256(self).color
        y = _make_Color256(c).color

        c = _Color256(c)
        return _Color256(x.red * y.red, x.green * y.green, x.blue * y.blue)

    def __pow__(self, c, mod):
        cdef ColorS x, y
        x = _make_Color256(self).color
        y = _make_Color256(c).color

        if mod is None:
            return _Color256(powFixed(x.red, y.red),
                                  powFixed(x.green, y.green),
                                  powFixed(x.blue, y.blue))

        m = _Color256(mod)
        return _Color256(pow(x.red, y.red, m.red),
                              pow(x.green, y.green, m.green),
                              pow(x.blue, y.blue, m.blue))

    def __sub__(self, c):
        cdef ColorS x, y
        x = _make_Color256(self).color
        y = _make_Color256(c).color

        return _Color256(x.red - y.red,
                              x.green - y.green,
                              x.blue - y.blue)

    # Everything else knows what self is!
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

    def __hash__(_Color256 self):
        # Sort of a hack.
        return (hash(self.color.red) +
                hash(self.color.blue) // 2 +
                hash(self.color.blue) // 4)

    @staticmethod
    def from_hex(uint32_t hex):
        """Create a color from a 32-bit unsigned integer."""
        cdef ColorS c
        c = colorFromHex(hex, integer)
        return _Color256(c.red, c.green, c.blue)

    cpdef to_hex(_Color256 self):
        """Convert a normalized color to a 32-bit integer."""
        if ((0 <= self.color.red <= 255.0) and
            (0 <= self.color.green <= 255.0) and
            (0 <= self.color.blue <= 255.0)):
            return hexFromColor(self.color, integer)
        raise ValueError(str(self) + " cannot be expressed in hex")

    def __invert__(_Color256 self):
        """Return the complementary color."""
        cdef float i
        i = 255 if (<int> integer == 1) else 1
        return _Color256(invert(self.color.red, i),
                            invert(self.color.green, i),
                            invert(self.color.blue, i))

    def __len__(_Color256 self):
        return 3

    def __neg__(_Color256 self):
        return _Color256(-self.color.red,
                              -self.color.green,
                              -self.color.blue)

    def __repr__(_Color256 self):
        return 'Color256(%s)' % str(self)

    def __richcmp__(_Color256 self, _Color256 c, int cmp):
        return cmpToRichcmp((self.color.red - c.color.red) or
                            (self.color.green - c.color.green) or
                            (self.color.blue - c.color.blue), cmp)

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


cdef _Color256 _make_Color256(object x):
    if isinstance(x, _Color256):
       return <_Color256> x
    return _Color256(x)
