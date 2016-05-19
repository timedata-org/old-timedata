import math, numbers

cdef class _Color{suffix}:
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
    def ratio(_Color{suffix} self):
        """Return the maximum ratio for this color range:  1.0 for Color
           and 255.0 for Color256."""
        return {ratio}

    cpdef rgb_to_hsv(_Color{suffix} self):
        """Return a new color converting RGB to HSV."""
        cdef ColorS c
        c = rgbToHsv(self.color, {base});
        return _Color{suffix}(c.red, c.green, c.blue)

    cpdef hsv_to_rgb(_Color{suffix} self):
        """Return a new color converting RGB to HSV."""
        cdef ColorS c
        c = hsvToRgb(self.color, {base});
        return _Color{suffix}(c.red, c.green, c.blue)

    def limited(_Color{suffix} self, *, min=None, max=None):
        """Return a new color limited to be not less than min (if given)
           and not greater than max (if given)."""
        cdef _Color{suffix} c
        c = self[:]
        if min is not None:
            minInto(_make_Color{suffix}(min).color, c.color)
        if max is not None:
            maxInto(_make_Color{suffix}(max).color, c.color)
        return c

    cpdef normalized(_Color{suffix} self):
        """Return a color normalized into this color range."""
        return _Color{suffix}(normalize(self.color.red, {ratio}),
                              normalize(self.color.green, {ratio}),
                              normalize(self.color.blue, {ratio}))

    cpdef rotated(_Color{suffix} self, int positions):
        """Return a color with the components rotated."""
        cdef _Color{suffix} c
        c = _Color{suffix}()
        c.color = rotate(self.color, positions)
        return c

    def __getitem__(_Color{suffix} self, object key):
        if isinstance(key, slice):
            r = tuple(self[i] for i in range(*key.indices(len(self))))
            return _Color{suffix}(*r) if len(r) == 3 else r

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
        x = _make_Color{suffix}(self).color
        y = _make_Color{suffix}(c).color
        return _Color{suffix}(x.red + y.red, x.green + y.green, x.blue + y.blue)

    def __truediv__(self, c):
        cdef ColorS x, y
        x = _make_Color{suffix}(self).color
        y = _make_Color{suffix}(c).color
        return _Color{suffix}(divFixed(x.red, y.red),
                              divFixed(x.green, y.green),
                              divFixed(x.blue, y.blue))

    def __divmod__(self, c):
        cdef ColorS x, y
        cdef float dr, mr, dg, mg, db, mb

        x = _make_Color{suffix}(self).color
        y = _make_Color{suffix}(c).color

        dr, mr = divmod(x.red, y.red)
        dg, mg = divmod(x.green, y.green)
        db, mb = divmod(x.blue, y.blue)
        return _Color{suffix}(dr, dg, db), _Color{suffix}(mr, mg, mb)

    def __mod__(self, c):
        cdef ColorS x, y
        x = _make_Color{suffix}(self).color
        y = _make_Color{suffix}(c).color

        return _Color{suffix}(x.red % y.red, x.green % y.green, x.blue % y.blue)

    def __mul__(self, c):
        cdef ColorS x, y
        x = _make_Color{suffix}(self).color
        y = _make_Color{suffix}(c).color

        c = _Color{suffix}(c)
        return _Color{suffix}(x.red * y.red, x.green * y.green, x.blue * y.blue)

    def __pow__(self, c, mod):
        cdef ColorS x, y
        x = _make_Color{suffix}(self).color
        y = _make_Color{suffix}(c).color

        if mod is None:
            return _Color{suffix}(powFixed(x.red, y.red),
                                  powFixed(x.green, y.green),
                                  powFixed(x.blue, y.blue))

        m = _Color{suffix}(mod)
        return _Color{suffix}(pow(x.red, y.red, m.red),
                              pow(x.green, y.green, m.green),
                              pow(x.blue, y.blue, m.blue))

    def __sub__(self, c):
        cdef ColorS x, y
        x = _make_Color{suffix}(self).color
        y = _make_Color{suffix}(c).color

        return _Color{suffix}(x.red - y.red,
                              x.green - y.green,
                              x.blue - y.blue)

    # Everything else knows what self is!
    def __abs__(_Color{suffix} self):
        return _Color{suffix}(abs(self.color.red),
                              abs(self.color.green),
                              abs(self.color.blue))

    def __ceil__(_Color{suffix} self):
        return _Color{suffix}(math.ceil(self.color.red),
                              math.ceil(self.color.green),
                              math.ceil(self.color.blue))

    def __floor__(_Color{suffix} self):
        return _Color{suffix}(math.floor(self.color.red),
                              math.floor(self.color.green),
                              math.floor(self.color.blue))

    def __hash__(_Color{suffix} self):
        # Sort of a hack.
        return (hash(self.color.red) +
                hash(self.color.blue) // 2 +
                hash(self.color.blue) // 4)

    @staticmethod
    def from_hex(uint32_t hex):
        """Create a color from a 32-bit unsigned integer."""
        cdef ColorS c
        c = colorFromHex(hex, {base})
        return _Color{suffix}(c.red, c.green, c.blue)

    cpdef to_hex(_Color{suffix} self):
        """Convert a normalized color to a 32-bit integer."""
        if ((0 <= self.color.red <= {ratio}) and
            (0 <= self.color.green <= {ratio}) and
            (0 <= self.color.blue <= {ratio})):
            return hexFromColor(self.color, {base})
        raise ValueError(str(self) + " cannot be expressed in hex")

    def __invert__(_Color{suffix} self):
        """Return the complementary color."""
        cdef float i
        i = 255 if (<int> {base} == 1) else 1
        return _Color{suffix}(invert(self.color.red, i),
                            invert(self.color.green, i),
                            invert(self.color.blue, i))

    def __len__(_Color{suffix} self):
        return 3

    def __neg__(_Color{suffix} self):
        return _Color{suffix}(-self.color.red,
                              -self.color.green,
                              -self.color.blue)

    def __repr__(_Color{suffix} self):
        return 'Color{suffix}(%s)' % str(self)

    def __richcmp__(_Color{suffix} self, _Color{suffix} c, int cmp):
        return cmpToRichcmp((self.color.red - c.color.red) or
                            (self.color.green - c.color.green) or
                            (self.color.blue - c.color.blue), cmp)

    def __round__(_Color{suffix} self, n):
        return _Color{suffix}(round(self.color.red, n),
                              round(self.color.green, n),
                              round(self.color.blue, n))

    def __str__(_Color{suffix} self):
        return colorToString(self.color, {base}).decode('ascii')

    def __sizeof__(_Color{suffix} self):
        return 12  # 3 4-byte floats.

    def __trunc__(_Color{suffix} self):
        return _Color{suffix}(math.trunc(self.color.red),
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


cdef _Color{suffix} _make_Color{suffix}(object x):
    if isinstance(x, _Color{suffix}):
       return <_Color{suffix}> x
    return _Color{suffix}(x)
