import math, numbers

cdef class OldColor{suffix}:
    """A OldColor is an immutable RGB floating point color.

       A OldColor looks very much like a Python tuple with three floating point
       numbers, with the big exception that operators like + and * perform
       arithmetic, not list-style operations.

       The constructor for OldColor takes a triple of numbers but also strings
       representing human-readable color names like "red" and "green".

       OldColor supports the operations +, -, *, /, %, pow, and ~ (which means
       "take the complementary color").

       OldColors are very lightweight - about half the size of a corresponding
       Python tuple and more than twice as fast to create and copy.  OldColors are
       also immutable - all operations on OldColors have to create a new OldColor.

       There are two ranges for color components.  The base class OldColor is
       normalized so that the standard range for output signals - that is,
       outout color components - is [0.0, 1.0].  As always, intermediate signals
       can be greater than 1 or even negative.

       The derived class OldColor256 has a standard output range of [0, 255] for
       better compatibility with existing RGB and DMX systems.
    """
    cdef OldColorS color

    def __init__(self, *args):
        """There are various different ways to construct a OldColor.
          * The empty constructor OldColor() gives OldColors.black where all
            components are zero.
          * OldColors can be constructed from string names.
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
                if stringToColor(args, self.color, {base}):
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
    def ratio(OldColor{suffix} self):
        """Return the maximum ratio for this color range:  1.0 for OldColor
           and 255.0 for OldColor256."""
        return {ratio}

    cpdef rgb_to_hsv(OldColor{suffix} self):
        """Return a new color converting RGB to HSV."""
        cdef OldColorS c
        c = rgbToHsv(self.color, {base});
        return OldColor{suffix}(c.red, c.green, c.blue)

    cpdef hsv_to_rgb(OldColor{suffix} self):
        """Return a new color converting RGB to HSV."""
        cdef OldColorS c
        c = hsvToRgb(self.color, {base});
        return OldColor{suffix}(c.red, c.green, c.blue)

    cpdef max_limit(OldColor{suffix} self, max):
        """Return a new color limited to be not greater than max."""
        cdef OldColor{suffix} c
        c = self[:]
        minInto(_toOldColor{suffix}(max).color, c.color)
        return c

    cpdef min_limit(OldColor{suffix} self, min):
        """Return a new color limited to be not less than min."""
        cdef OldColor{suffix} c
        c = self[:]
        maxInto(_toOldColor{suffix}(min).color, c.color)
        return c

    cpdef distance(OldColor{suffix} self, OldColor{suffix} other):
        """Return the cartesian distance between this color and another."""
        return distance(self.color, other.color)

    cpdef distance2(OldColor{suffix} self, OldColor{suffix} other):
        """Return the square of the cartesian distance between this color and
           another - this is somewhat more efficient and often good enough."""
        return distance2(self.color, other.color)

    cpdef normalized(OldColor{suffix} self):
        """Return a color normalized into this color range."""
        return OldColor{suffix}(normalize(self.color.red, {ratio}),
                             normalize(self.color.green, {ratio}),
                             normalize(self.color.blue, {ratio}))

    cpdef rotated(OldColor{suffix} self, int positions):
        """Return a color with the components rotated."""
        cdef OldColor{suffix} c
        c = OldColor{suffix}()
        c.color = rotate(self.color, positions)
        return c

    def __getitem__(OldColor{suffix} self, object key):
        if isinstance(key, slice):
            r = tuple(self[i] for i in range(*key.indices(len(self))))
            return OldColor{suffix}(*r) if len(r) == 3 else r

        if key == 0 or key == -3:
            return self.color.red
        if key == 1 or key == -2:
            return self.color.green
        if key == 2 or key == -1:
            return self.color.blue
        raise IndexError('OldColor index out of range')

    # Operations where self is *not* necessarily a color!
    # This can happen if "self" appear on the right in an operation.
    # So all of these are wrong in fact.  :-D
    def __add__(self, c):
        cdef OldColorS x, y
        x = _toOldColor{suffix}(self).color
        y = _toOldColor{suffix}(c).color
        return OldColor{suffix}(x.red + y.red, x.green + y.green, x.blue + y.blue)

    def __truediv__(self, c):
        cdef OldColorS x, y
        x = _toOldColor{suffix}(self).color
        y = _toOldColor{suffix}(c).color
        return OldColor{suffix}(divPython(x.red, y.red),
                              divPython(x.green, y.green),
                              divPython(x.blue, y.blue))

    def __divmod__(self, c):
        cdef OldColorS x, y
        cdef float dr, mr, dg, mg, db, mb

        x = _toOldColor{suffix}(self).color
        y = _toOldColor{suffix}(c).color

        dr, mr = divmod(x.red, y.red)
        dg, mg = divmod(x.green, y.green)
        db, mb = divmod(x.blue, y.blue)
        return OldColor{suffix}(dr, dg, db), OldColor{suffix}(mr, mg, mb)

    def __mod__(self, c):
        cdef OldColorS x, y
        x = _toOldColor{suffix}(self).color
        y = _toOldColor{suffix}(c).color

        return OldColor{suffix}(x.red % y.red, x.green % y.green, x.blue % y.blue)

    def __mul__(self, c):
        cdef OldColorS x, y
        x = _toOldColor{suffix}(self).color
        y = _toOldColor{suffix}(c).color

        c = OldColor{suffix}(c)
        return OldColor{suffix}(x.red * y.red, x.green * y.green, x.blue * y.blue)

    def __pow__(self, c, mod):
        cdef OldColorS x, y
        x = _toOldColor{suffix}(self).color
        y = _toOldColor{suffix}(c).color

        if mod is None:
            return OldColor{suffix}(powPython(x.red, y.red),
                                  powPython(x.green, y.green),
                                  powPython(x.blue, y.blue))

        m = OldColor{suffix}(mod)
        return OldColor{suffix}(pow(x.red, y.red, m.red),
                              pow(x.green, y.green, m.green),
                              pow(x.blue, y.blue, m.blue))

    def __sub__(self, c):
        cdef OldColorS x, y
        x = _toOldColor{suffix}(self).color
        y = _toOldColor{suffix}(c).color

        return OldColor{suffix}(x.red - y.red,
                              x.green - y.green,
                              x.blue - y.blue)

    def __abs__(OldColor{suffix} self):
        return OldColor{suffix}(abs(self.color.red),
                              abs(self.color.green),
                              abs(self.color.blue))

    def __ceil__(OldColor{suffix} self):
        return OldColor{suffix}(math.ceil(self.color.red),
                              math.ceil(self.color.green),
                              math.ceil(self.color.blue))

    def __floor__(OldColor{suffix} self):
        return OldColor{suffix}(math.floor(self.color.red),
                              math.floor(self.color.green),
                              math.floor(self.color.blue))

    def __hash__(OldColor{suffix} self):
        # Sort of a hack.
        return (hash(self.color.red) +
                hash(self.color.blue) // 2 +
                hash(self.color.blue) // 4)

    @staticmethod
    def from_hex(uint32_t hex):
        """Create a color from a 32-bit unsigned integer."""
        cdef OldColorS c
        c = colorFromHex(hex, {base})
        return OldColor{suffix}(c.red, c.green, c.blue)

    cpdef to_hex(OldColor{suffix} self):
        """Convert a normalized color to a 32-bit integer."""
        if ((0 <= self.color.red <= {ratio}) and
            (0 <= self.color.green <= {ratio}) and
            (0 <= self.color.blue <= {ratio})):
            return hexFromColor(self.color, {base})
        raise ValueError(str(self) + " cannot be expressed in hex")

    def __invert__(OldColor{suffix} self):
        """Return the complementary color."""
        cdef float i
        i = 255 if (<int> {base} == 1) else 1
        return OldColor{suffix}(invert(self.color.red, i),
                            invert(self.color.green, i),
                            invert(self.color.blue, i))

    def __len__(OldColor{suffix} self):
        return 3

    def __neg__(OldColor{suffix} self):
        return OldColor{suffix}(-self.color.red,
                             -self.color.green,
                             -self.color.blue)

    def __repr__(OldColor{suffix} self):
        return 'OldColor{suffix}(%s)' % str(self)

    def __richcmp__(OldColor{suffix} self, OldColor{suffix} c, int cmpType):
        return cmpToRichcmp(cmp(self.color, c.color), cmpType)

    def __round__(OldColor{suffix} self, n):
        return OldColor{suffix}(round(self.color.red, n),
                             round(self.color.green, n),
                             round(self.color.blue, n))

    def __str__(OldColor{suffix} self):
        return colorToString(self.color, {base}).decode('ascii')

    def __trunc__(OldColor{suffix} self):
        return OldColor{suffix}(math.trunc(self.color.red),
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


cdef OldColor{suffix} _toOldColor{suffix}(object x):
    if isinstance(x, OldColor{suffix}):
       return <OldColor{suffix}> x
    return OldColor{suffix}(x)
