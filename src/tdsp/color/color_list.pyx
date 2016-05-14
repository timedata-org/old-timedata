from numbers import Number

cdef extern from "<tdsp/color/colorList_inl.h>" namespace "tdsp":
    ColorList duplicate(ColorList&, int)
    void reverse(ColorList&)
    string toString(ColorList&)
    string toString(ColorList&, Base)
    ColorList sliceVector(ColorList&, int begin, int end, int step)
    int compareContainers(ColorList&, ColorList&)
    bool sliceIntoVector(ColorList& _in, ColorList& out,
                         int begin, int end, int step)

    void absColor(ColorList&)
    void negateColor(ColorList&)
    void invertColor(ColorList&)

    void addInto(float f, ColorList& out)
    void addInto(ColorList&, ColorList& out)

    void divideInto(float f, ColorList& out)
    void divideInto(ColorList&, ColorList& out)

    void minInto(float f, ColorList& out)
    void minInto(ColorList&, ColorList& out)

    void maxInto(float f, ColorList& out)
    void maxInto(ColorList&, ColorList& out)

    void multiplyInto(float f, ColorList& out)
    void multiplyInto(ColorList&, ColorList& out)

    void powInto(float f, ColorList& out)
    void powInto(ColorList&, ColorList& out)

    void rdivideInto(float f, ColorList& out)
    void rdivideInto(ColorList&, ColorList& out)

    void rpowInto(float f, ColorList& out)
    void rpowInto(ColorList&, ColorList& out)

    void rsubtractInto(float f, ColorList& out)
    void rsubtractInto(ColorList&, ColorList& out)

    void subtractInto(float f, ColorList& out)
    void subtractInto(ColorList&, ColorList& out)


cdef class _ColorList:
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
        if key >= self.colors.size():
            raise IndexError('Color index out of range')
        if key < 0:
            key += self.colors.size()
            if key < 0:
                raise IndexError('Color index out of range')
        return key

    cdef _ColorList _make(self, object value=None):
        return _ColorList(value, color_maker=self._color_maker,
                          class_name=self.class_name)

    cdef _ColorList _toColorList(self, object value):
        if isinstance(value, _ColorList):
            return <_ColorList> value
        else:
            return self._make(value)

    def __cinit__(self, items=None, *,
                  color_maker=_Color, class_name=u'ColorList'):
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
        cdef _ColorList cl
        if isinstance(key, slice):
            begin, end, step = key.indices(self.colors.size())
            print(type(x))
            cl = self._toColorList(x)
            if not sliceIntoVector(cl.colors, self.colors, begin, end, step):
                raise ValueError('attempt to assign sequence of one size '
                                 'to extended slice of another size')
        else:
            self.set_obj(self._fix_key(key), x)

    def abs(self):
        absColor(self.colors)

    def append(self, object value):
        cdef uint s
        s = self.colors.size()
        self.colors.resize(s + 1)
        try:
            self._set_obj(s, value)
        except:
            self.colors.resize(s)
            raise

    def clear(self):
        self.colors.clear()

    def reverse(self):
        reverse(self.colors)

    def duplicate(self, uint count):
        cl = self._make()
        cl.colors = duplicate(self.colors, count)
        return cl

    def extend(self, object values):
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
        """Convert to complementary colors."""
        invertColor(self.colors)

    def max(self, c):
        if isinstance(c, Number):
            maxInto(<float> c, self.colors)
        else:
            maxInto(self._toColorList(c).colors, self.colors)

    def min(self, c):
        if isinstance(c, Number):
            minInto(<float> c, self.colors)
        else:
            minInto(self._toColorList(c).colors, self.colors)

    def negate(self):
        negateColor(self.colors)

    def pow(self, c):
        if isinstance(c, Number):
            powInto(<float> c, self.colors)
        else:
            powInto(self._toColorList(c).colors, self.colors)

    def rpow(self, c):
        if isinstance(c, Number):
            rpowInto(<float> c, self.colors)
        else:
            rpowInto(self._toColorList(c).colors, self.colors)

    # Mutating operations.
    def __iadd__(self, c):
        if isinstance(c, Number):
            addInto(<float> c, self.colors)
        else:
            addInto(self._toColorList(c).colors, self.colors)

    def __imul__(self, c):
        if isinstance(c, Number):
            multiplyInto(<float> c, self.colors)
        else:
            multiplyInto(self._toColorList(c).colors, self.colors)

    def __isub__(self, c):
        if isinstance(c, Number):
             subtractInto(<float> c, self.colors)
        else:
             subtractInto(self._toColorList(c).colors, self.colors)

    def __itruediv__(self, c):
        if isinstance(c, Number):
            divideInto(<float> c, self.colors)
        else:
            divideInto(self._toColorList(c).colors, self.colors)

    # Operations where self is on the left side.
    def __add__(self, c):
        cl = self[:]
        cl += c
        return cl

    # Operations where self is on the left side.
    def __mul__(self, c):
        cl = self[:]
        cl *= c
        return cl

    # Operations where self is on the left side.
    def __sub__(self, c):
        cl = self[:]
        cl -= c
        return cl

    def __truediv__(self, c):
        cl = self[:]
        cl /= c
        return cl

    def __pow__(self, c, mod):
        if mod is not None:
            raise ValueError("Don't understand three-operator mod")
        cl = self[:]
        cl.pow(c)
        return c

    # Operations where self is on the right side.
    def __radd__(self, c):
        return self + c

    def __rdiv__(self, c):
        if isinstance(c, Number):
             rdivideInto(<float> c, self.colors)
        else:
             rdivideInto(self._toColorList(c).colors, self.colors)

    def __rmul__(self, c):
        return self * c

    def __rpow__(self, c, mod):
        if mod is not None:
            raise ValueError("Don't understand three-operator mod")
        cl = self[:]
        cl.rpow(c)
        return c

    def __rsub__(self, c):
        if isinstance(c, Number):
             rsubtractInto(<float> c, self.colors)
        else:
             rsubtractInto(self._toColorList(c).colors, self.colors)

    def __len__(self):
        return self.colors.size()

    def __repr__(self):
        return '%s(%s)' % (self.class_name, str(self))

    def __richcmp__(_ColorList self, _ColorList other, int rcmp):
        if self._color_maker is not other._color_maker:
            raise ValueError('Can\'t compare two different color models.')
        return cmpToRichcmp(compareContainers(self.colors, other.colors), rcmp)

    def __str__(self):
        return toString(self.colors, (<_Color> self._color_maker())._base()
                        ).decode('ascii')


def _ColorList256(*args, **kwds):
    cl = _ColorList(*args, color_maker=_Color256, class_name=u'ColorList256',
                    **kwds)
    return cl
