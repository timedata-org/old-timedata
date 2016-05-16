from numbers import Number

cdef class CColorList:
    """A list of RGB floating point Colors, with many mutating functions.

       A ColorList looks quite like a Python list of Colors (which look like
       tuples) with the big interface difference that operations like + and *
       perform arithmetic and not list construction.

       Written in C++, this class should consume significantly fewer memory and
       CPU resources than a corresponding Python list, as well as providing a
       range of useful facilities.

       While ColorList provides a full set of functions and operations that
       create new ColorLists, in each case there is a corresponding mutating
       function or operation that works "in-place" with no heap allocations
       at all, for best performance.

       The base class ColorList is a list of Color, which are normalized to
       [0, 1]; the derived class ColorList256 is a list of Color256, which
       are normalized to [0, 255].
"""
    cdef ColorList colors

    def __cinit__(self, items=None):
        """Construct a ColorList with an iterator of items, each of which looks
           like a Color."""
        if items is not None:
            if instanceof(items, CColorList):
                self.colors = (<CColorList> items).colors
            else:
                # A list of tuples, Colors or strings.
                self.colors.resize(len(items))
                for i, item in enumerate(items):
                    self[i] = item

    def __setitem__(self, object key, object x):
        cdef size_t length, slice_length, index
        cdef int begin, end, step
        float r, g, b
        cdef CColorList cl
        if isinstance(key, slice):
            begin, end, step = key.indices(self.colors.size())
            if sliceIntoVector(toCL(x).colors, self.colors,
                               begin, end, step):
                return
            raise ValueError('attempt to assign sequence of one size '
                             'to extended slice of another size')
        index = key
        if not fixKey(key):
            raise IndexError('ColorList index out of range')
        if isinstance(x, str):
            x = Color(x)
        r, g, b = x
        self.colors.setColor(i, r, g, b)

    def __getitem__(self, object key):
        cdef Color c
        if isinstance(key, slice):
            begin, end, step = key.indices(self.colors.size())
            cl = ColorList()
            cl.colors = sliceVector(self.colors, begin, end, step)
            return cl

        c = self.colors[self._fix_key(key)]
        return _Color(c.at(0), c.at(1), c.at(2))

    def abs(self):
        """Replace each color by its absolute value."""
        absColor(self.colors)

    def append(self, object value):
        """Append to the list of colors."""
        cdef uint s
        s = self.colors.size()
        self.colors.resize(s + 1)
        try:
            this[s] = value
        except:
            self.colors.resize(s)
            raise

    def clear(self):
        """Set all colors to black."""
        self.colors.clear()

    def rotate(self, int pos):
        """Rotate the colors forward by `pos` positions."""
        rotate(self.colors, pos)

    def reverse(self):
        """Reverse the colors in place."""
        reverse(self.colors)

    def duplicate(self, uint count):
        """Return a new `ColorList` with `count` copies of this one."""
        cl = CColorList()
        cl.colors = duplicate(self.colors, count)
        return cl

    def extend(self, object values):
        """Extend the colors from an iterator."""
        cdef size_t s
        s = self.colors.size()
        try:
            for v in values:
                self.append(v)
        except:
            self.colors.resize(s)
            raise

    def invert(self):
        """Invert each colors to its complement."""
        invertColor(self.colors)

    def max(self, c):
        """Mutate each color by max-ing it with a number or a ColorList."""
        if isinstance(c, Number):
            maxInto(<float> c, self.colors)
        else:
            maxInto(_toCL(c).colors, self.colors)

    def min(self, c):
        """Mutate each color by min-ing it with a number or a ColorList."""
        if isinstance(c, Number):
            minInto(<float> c, self.colors)
        else:
            minInto(_toCL(c).colors, self.colors)

    def negate(self):
        """Negate each color."""
        negateColor(self.colors)

    def pow(self, float c):
        """Raise each color to the given power (gamma correction)."""
        if isinstance(c, Number):
            powInto(<float> c, self.colors)
        else:
            powInto(_toCL(c).colors, self.colors)

    def resize(self, size_t size):
        """Set the size of the ColorList, filling with black if needed."""
        self.colors.resize(size)

    def rpow(self, c):
        """Right-hand (reversed) reverse of pow()."""
        if isinstance(c, Number):
            rpowInto(<float> c, self.colors)
        else:
            rpowInto(_toCL(c).colors, self.colors)

    # Mutating operations.
    def __iadd__(self, c):
        if isinstance(c, Number):
            addInto(<float> c, self.colors)
        else:
            addInto(_toCL(c).colors, self.colors)
        return self

    def __imul__(self, c):
        if isinstance(c, Number):
            multiplyInto(<float> c, self.colors)
        else:
            multiplyInto(_toCL(c).colors, self.colors)

    def __ipow__(self, c):
        if isinstance(c, Number):
             powInto(<float> c, self.colors)
        else:
             powInto(_toCL(c).colors, self.colors)

    def __isub__(self, c):
        if isinstance(c, Number):
             subtractInto(<float> c, self.colors)
        else:
             subtractInto(_toCL(c).colors, self.colors)

    def __itruediv__(self, c):
        if isinstance(c, Number):
            divideInto(<float> c, self.colors)
        else:
            divideInto(_toCL(c).colors, self.colors)

    def __add__(self, c):
        CColorList cl
        if isinstance(c, Number):
            addOver(self.colors, <float> c, cl.colors)
        elif isinstance(self, CColorList):
            addOver(self.colors, _toCL(c).colors, cl.colors)
        else:
            addOver(ColorList(self).colors, c, cl.colors)
        return cl

    def __mul__(self, c):
        CColorList cl
        if isinstance(c, Number):
            mulOver(self.colors, <float> c, cl.colors)
        elif isinstance(self, CColorList):
            mulOver(self.colors, _toCL(c).colors, cl.colors)
        else:
            mulOver(ColorList(self).colors, c, cl.colors)
        return cl

    def __sub__(self, c):
        CColorList cl
        if isinstance(c, Number):
            subOver(self.colors, <float> c, cl.colors)
        elif isinstance(self, CColorList):
            subOver(self.colors, _toCL(c).colors, cl.colors)
        else:
            subOver(ColorList(self).colors, c, cl.colors)
        return cl

    def __truediv__(self, c):
        CColorList cl
        if isinstance(c, Number):
            divOver(self.colors, <float> c, cl.colors)
        elif isinstance(self, CColorList):
            divOver(self.colors, _toCL(c).colors, cl.colors)
        else:
            divOver(ColorList(self).colors, c, cl.colors)
        return cl

    def __pow__(self, c, mod):
        if mod is not None:
            raise ValueError("Don't understand three-operator mod")
        CColorList cl
        if isinstance(c, Number):
            powOver(self.colors, <float> c, cl.colors)
        elif isinstance(self, CColorList):
            powOver(self.colors, _toCL(c).colors, cl.colors)
        else:
            powOver(ColorList(self).colors, c, cl.colors)
        return c

    def __len__(self):
        return self.colors.size()

    def __repr__(self):
        return 'CColorList(%s)' % str(self)

    def __richcmp__(CColorList self, CColorList other, int rcmp):
        if self._color_maker is not other._color_maker:
            raise ValueError('Can\'t compare two different color models.')
        return cmpToRichcmp(compareContainers(self.colors, other.colors), rcmp)

    def __sizeof__(self):
        # 12 bytes per color plus two pointers.
        return 12 * self.colors.size() + 8 + 8

    def __str__(self):
        return toString(self.colors).decode('ascii')

cdef CColorList toCL(object value):
    if isinstance(value, CColorList):
        return <CColorList> value
    else:
        return CColorList(value)
