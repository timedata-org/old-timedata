from numbers import Number

cdef class OperatorColorList:
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
    cdef object _color_maker
    cdef unicode class_name

    cdef _set(self, uint i, float r, float g, float b):
       self.colors[i] = makeColor(r, g, b)

    def _set_obj(self, uint i, object x):
        if isinstance(x, str):
            c = self._color_maker(x)
            self._set(i, c.red, c.green, c.blue)
        else:
            r, g, b = x
            self._set(i, r, g, b)

    cdef _fix_key(self, int key):
        if key < 0:
            key += self.colors.size()
            if key < 0:
                raise IndexError('Color index out of range (1)')
        if key >= self.colors.size():
            raise IndexError('Color index out of range (2)')
        return key

    cdef OperatorColorList _make(self, object value=None):
        return OperatorColorList(value, color_maker=self._color_maker,
                          class_name=self.class_name)

    cdef OperatorColorList _toColorList(self, object value):
        if isinstance(value, OperatorColorList):
            return <OperatorColorList> value
        else:
            return self._make(value)

    cdef OperatorColorList _run_new_unary(self, Unary op):
        cdef OperatorColorList result
        result = self._make()
        runTogether(op, self.colors, result.colors)
        return result

    @staticmethod
    cdef OperatorColorList _run_new(object x, object y, Binary op):
        """An operation that creates a new ColorList."""
        cdef OperatorColorList cl, result
        cdef Side side
        if isinstance(x, OperatorColorList):
            side = LEFT
            cl = x
        else:
            side = RIGHT
            cl = y
            y = x
        result = cl._make()
        if isinstance(y, Number):
            runTogether(op, side, cl.colors, <float> y, result.colors)
        else:
            runTogether(
                op, side, cl.colors, cl._toColorList(y).colors, result.colors)
        return result

    cdef _run_into(self, object x, Binary op, Side side=LEFT):
        """An operation that mutates this ColorList."""
        if isinstance(x, Number):
            runInto(op, side, <float> x, self.colors)
        else:
            runInto(op, side, self._toColorList(x).colors, self.colors)
        return self

    def __cinit__(self, items=None, *,
                  color_maker=_Color, class_name=u'ColorList'):
        """Construct a ColorList with an iterator of items, each of which looks
           like a Color."""
        self._color_maker = color_maker
        self.class_name = class_name
        if items:
            # Make a guess as to whether it's a list of integers or not.
            try:
                len(items[0])
            except:
                # A list of integers
                assert not (len(items) % 3)
                self.colors.resize(<size_t> (len(items) / 3))
                for i in range(0, len(items), 3):
                    self._set(i, items[i], items[i + 1], items[i + 2])
            else:
                # A list of tuples, Colors or strings.
                self.colors.resize(len(items))
                for i, item in enumerate(items):
                    self._set_obj(i, item)

    def __getitem__(self, object key):
        cdef Color c
        if isinstance(key, slice):
            begin, end, step = key.indices(self.colors.size())
            cl = self._make()
            cl.colors = sliceVector(self.colors, begin, end, step)
            return cl

        c = self.colors[self._fix_key(key)]
        return self._color_maker(c.at(0), c.at(1), c.at(2))

    def __setitem__(self, object key, object x):
        cdef size_t length, slice_length
        cdef int begin, end, step
        cdef OperatorColorList cl
        if isinstance(key, slice):
            begin, end, step = key.indices(self.colors.size())
            if not sliceIntoVector(self._toColorList(x).colors, self.colors,
                                   begin, end, step):
                raise ValueError('attempt to assign sequence of one size '
                                 'to extended slice of another size')
        else:
            self._set_obj(self._fix_key(key), x)

    def abs(self):
        """Replace each color by its absolute value."""
        runInto(ABS, self.colors)

    def append(self, object value):
        """Append to the list of colors."""
        cdef uint s
        s = self.colors.size()
        self.colors.resize(s + 1)
        try:
            self._set_obj(s, value)
        except:
            # TODO: this is a little inefficient, but only happens
            # in error cases, which only happen in development.
            self.colors.resize(s)
            raise

    def clear(self):
        """Set all colors to black."""
        runInto(CLEAR, self.colors)

    def rotate(self, int pos):
        """Rotate the colors forward by `pos` positions."""
        rotate(self.colors, pos)

    def reverse(self):
        """Reverse the colors in place."""
        reverse(self.colors)

    def duplicate(self, uint count):
        """Return a new `ColorList` with `count` copies of this one."""
        cl = self._make()
        cl.colors = duplicate(self.colors, count)
        return cl

    def extend(self, object values):
        """Extend the colors from an iterator."""
        cdef uint s
        s = self.colors.size()
        self.colors.resize(s + len(values))
        try:
            for i, v in enumerate(values):
                self._set_obj(s + i, v)
        except:
            self.colors.resize(s)
            raise

    def invert(self):
        """Invert each color to its complement."""
        runInto(INVERT, self.colors)

    def max(self, object x):
        """Mutate each color by max-ing it with a number or a ColorList."""
        return self._run_into(x, MAX)

    def min(self, x):
        """Mutate each color by min-ing it with a number or a ColorList."""
        return self._run_into(x, MIN)

    def negate(self):
        """Negate each color."""
        runInto(INVERT, self.colors)

    def resize(self, size_t size):
        """Set the size of the ColorList, filling with black if needed."""
        self.colors.resize(size)

    def rpow(self, x):
        """Right-hand (reversed) reverse of pow()."""
        return self._run_into(x, POW, RIGHT)

    def __iadd__(self, x):     return self._run_into(x, ADD)
    def __imul__(self, x):     return self._run_into(x, MUL)
    def __ipow__(self, x):     return self._run_into(x, POW)
    def __isub__(self, x):     return self._run_into(x, SUB)
    def __itruediv__(self, x): return self._run_into(x, DIV)

    def __add__(self, x):      return OperatorColorList._run_new(self, x, ADD)
    def __mul__(self, x):      return OperatorColorList._run_new(self, x, MUL)
    def __sub__(self, x):      return OperatorColorList._run_new(self, x, SUB)
    def __truediv__(self, x):  return OperatorColorList._run_new(self, x, DIV)

    def __pow__(self, x, mod):
        assert not mod, 'Don\'t understand three color mod'
        return OperatorColorList._run_new(self, x, POW)

    def __len__(self):
        return self.colors.size()

    def __repr__(self):
        return '%s(%s)' % (self.class_name, str(self))

    def __richcmp__(OperatorColorList self, OperatorColorList other, int rcmp):
        if not other:
            raise TypeError('Can\'t order with None')

        if self._color_maker is not other._color_maker:
            raise ValueError('Can\'t compare two different color models.')
        return cmpToRichcmp(compareContainers(self.colors, other.colors), rcmp)

    def __sizeof__(self):
        # 12 bytes per color plus two pointers.
        return 12 * self.colors.size() + 8 + 8

    def __str__(self):
        s = toString(self.colors, (<_Color> self._color_maker())._base())
        return s.decode('ascii')


def OperatorColorList256(*args, **kwds):
    cl = OperatorColorList(*args, color_maker=_Color256, class_name=u'ColorList256',
                    **kwds)
    return cl
