import math, numbers

cdef class Color:
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

       There are two ranges for color components.  The base class Color is
       normalized so that the standard range for output signals - that is,
       outout color components - is [0.0, 1.0].  As always, intermediate signals
       can be greater than 1 or even negative.

       The derived class Color256 has a standard output range of [0, 255] for
       better compatibility with existing RGB and DMX systems.
    """
    cdef ColorS color

    def __init__(self, *args):
        """There are various different ways to construct a Color.
          * The empty constructor Color() gives Colors.black where all
            components are zero.
          * Colors can be constructed from string names.
          * Constructing from a single number results in a color with all three
            components of that value.
          * Constructing from any sort of triplet assigns these values to red,
            green and blue."""
        if not args:
            self.color.red = self.color.green = self.color.blue = 0
            return

        if len(args) == 1:
            args = args[0]
            if isinstance(args, numbers.Number):
                self.color.red = self.color.green = self.color.blue = args
                return

            if isinstance(args, str):
                if stringToColor(args, self.color, normal):
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
    def ratio(Color self):
        """Return the maximum ratio for this color range:  1.0 for Color
           and 255.0 for Color256."""
        return 1.0

    cpdef rgb_to_hsv(Color self):
        """Return a new color converting RGB to HSV."""
        cdef ColorS c
        c = rgbToHsv(self.color, normal);
        return Color(c.red, c.green, c.blue)

    cpdef hsv_to_rgb(Color self):
        """Return a new color converting RGB to HSV."""
        cdef ColorS c
        c = hsvToRgb(self.color, normal);
        return Color(c.red, c.green, c.blue)

    cpdef max_limit(Color self, max):
        """Return a new color limited to be not greater than max."""
        cdef Color c
        c = self[:]
        minInto(_toColor(max).color, c.color)
        return c

    cpdef min_limit(Color self, min):
        """Return a new color limited to be not less than min."""
        cdef Color c
        c = self[:]
        maxInto(_toColor(min).color, c.color)
        return c

    cpdef distance(Color self, Color other):
        """Return the cartesian distance between this color and another."""
        return distance(self.color, other.color)

    cpdef distance2(Color self, Color other):
        """Return the square of the cartesian distance between this color and
           another - this is somewhat more efficient and often good enough."""
        return distance2(self.color, other.color)

    cpdef normalized(Color self):
        """Return a color normalized into this color range."""
        return Color(normalize(self.color.red, 1.0),
                             normalize(self.color.green, 1.0),
                             normalize(self.color.blue, 1.0))

    cpdef rotated(Color self, int positions):
        """Return a color with the components rotated."""
        cdef Color c
        c = Color()
        c.color = rotate(self.color, positions)
        return c

    def __getitem__(Color self, object key):
        if isinstance(key, slice):
            r = tuple(self[i] for i in range(*key.indices(len(self))))
            return Color(*r) if len(r) == 3 else r

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
        x = _toColor(self).color
        y = _toColor(c).color
        return Color(x.red + y.red, x.green + y.green, x.blue + y.blue)

    def __truediv__(self, c):
        cdef ColorS x, y
        x = _toColor(self).color
        y = _toColor(c).color
        return Color(divFixed(x.red, y.red),
                              divFixed(x.green, y.green),
                              divFixed(x.blue, y.blue))

    def __divmod__(self, c):
        cdef ColorS x, y
        cdef float dr, mr, dg, mg, db, mb

        x = _toColor(self).color
        y = _toColor(c).color

        dr, mr = divmod(x.red, y.red)
        dg, mg = divmod(x.green, y.green)
        db, mb = divmod(x.blue, y.blue)
        return Color(dr, dg, db), Color(mr, mg, mb)

    def __mod__(self, c):
        cdef ColorS x, y
        x = _toColor(self).color
        y = _toColor(c).color

        return Color(x.red % y.red, x.green % y.green, x.blue % y.blue)

    def __mul__(self, c):
        cdef ColorS x, y
        x = _toColor(self).color
        y = _toColor(c).color

        c = Color(c)
        return Color(x.red * y.red, x.green * y.green, x.blue * y.blue)

    def __pow__(self, c, mod):
        cdef ColorS x, y
        x = _toColor(self).color
        y = _toColor(c).color

        if mod is None:
            return Color(powFixed(x.red, y.red),
                                  powFixed(x.green, y.green),
                                  powFixed(x.blue, y.blue))

        m = Color(mod)
        return Color(pow(x.red, y.red, m.red),
                              pow(x.green, y.green, m.green),
                              pow(x.blue, y.blue, m.blue))

    def __sub__(self, c):
        cdef ColorS x, y
        x = _toColor(self).color
        y = _toColor(c).color

        return Color(x.red - y.red,
                              x.green - y.green,
                              x.blue - y.blue)

    def __abs__(Color self):
        return Color(abs(self.color.red),
                              abs(self.color.green),
                              abs(self.color.blue))

    def __ceil__(Color self):
        return Color(math.ceil(self.color.red),
                              math.ceil(self.color.green),
                              math.ceil(self.color.blue))

    def __floor__(Color self):
        return Color(math.floor(self.color.red),
                              math.floor(self.color.green),
                              math.floor(self.color.blue))

    def __hash__(Color self):
        # Sort of a hack.
        return (hash(self.color.red) +
                hash(self.color.blue) // 2 +
                hash(self.color.blue) // 4)

    @staticmethod
    def from_hex(uint32_t hex):
        """Create a color from a 32-bit unsigned integer."""
        cdef ColorS c
        c = colorFromHex(hex, normal)
        return Color(c.red, c.green, c.blue)

    cpdef to_hex(Color self):
        """Convert a normalized color to a 32-bit integer."""
        if ((0 <= self.color.red <= 1.0) and
            (0 <= self.color.green <= 1.0) and
            (0 <= self.color.blue <= 1.0)):
            return hexFromColor(self.color, normal)
        raise ValueError(str(self) + " cannot be expressed in hex")

    def __invert__(Color self):
        """Return the complementary color."""
        cdef float i
        i = 255 if (<int> normal == 1) else 1
        return Color(invert(self.color.red, i),
                            invert(self.color.green, i),
                            invert(self.color.blue, i))

    def __len__(Color self):
        return 3

    def __neg__(Color self):
        return Color(-self.color.red,
                             -self.color.green,
                             -self.color.blue)

    def __repr__(Color self):
        return 'Color(%s)' % str(self)

    def __richcmp__(Color self, Color c, int cmpType):
        return cmpToRichcmp(cmp(self.color, c.color), cmpType)

    def __round__(Color self, n):
        return Color(round(self.color.red, n),
                             round(self.color.green, n),
                             round(self.color.blue, n))

    def __str__(Color self):
        return colorToString(self.color, normal).decode('ascii')

    def __trunc__(Color self):
        return Color(math.trunc(self.color.red),
                             math.trunc(self.color.green),
                             math.trunc(self.color.blue))

    @staticmethod
    def names():
        """Return a list of all the known color names."""
        cdef vector[string] names
        result = []
        names = colorNames()
        for i in names:
            result.append(i.decode('ascii'))
        return result


cdef Color _toColor(object x):
    if isinstance(x, Color):
       return <Color> x
    return Color(x)
