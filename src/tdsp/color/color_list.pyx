cdef extern from "<tdsp/color/colorList.h>" namespace "tdsp":
    ctypedef vector[Color] ColorList

    ColorList duplicate(ColorList&, int)
    void reverse(ColorList&)
    string toString(ColorList&)
    ColorList sliceVector(ColorList&, int begin, int end, int step)
    int compareContainers(ColorList&, ColorList&)
    bool sliceIntoVector(ColorList& _in, ColorList& out,
                         int begin, int end, int step)

    void absColor(ColorList&)
    void negateColor(ColorList&)
    void invertColor(ColorList&)

cdef _ColorList _toColorList(object value):
    if isinstance(value, _ColorList):
        return <_ColorList> value
    else:
        return _ColorList(value)

cdef class _ColorList:
    cdef ColorList colors

    cdef _set(self, uint i, float r, float g, float b):
       self.colors[i] = makeColor(r, g, b)

    def _set_obj(self, uint i, object x):
        if isinstance(x, str):
            c = _Color(x)
            self._set(i, c.red, c.green, c.blue)
        else:
            r, g, b = x
            self._set(i, r, g, b)

    def __cinit__(self, items=None):
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

    def _fix_key(self, int key):
        if key >= self.colors.size():
            raise IndexError('Color index out of range')
        if key < 0:
            key += self.colors.size()
            if key < 0:
                raise IndexError('Color index out of range')
        return key

    def __getitem__(self, object key):
        cdef Color c
        if isinstance(key, slice):
            begin, end, step = key.indices(self.colors.size())
            cl = _ColorList()
            cl.colors = sliceVector(self.colors, begin, end, step)
            return cl

        c = self.colors[self._fix_key(key)]
        return _Color(c.at(0), c.at(1), c.at(2))

    def __setitem__(self, object key, object x):
        cdef size_t length, slice_length
        cdef int begin, end, step
        if isinstance(key, slice):
            begin, end, step = key.indices(self.colors.size())
            if not sliceIntoVector(_toColorList(x).colors,
                                   self.colors, begin, end, step):
                raise ValueError('attempt to assign sequence of one size '
                                 'to extended slice of another size')
        else:
            self.set_obj(self._fix_key(key), x)

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
        cl = _ColorList()
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

    def abs(self):
        absColor(self.colors)

    # def __add__(self, c):
    #     c = _Color(c)
    #     return Color(self.red + c.red, self.green + c.green, self.blue + c.blue)

    # def __div__(self, c):
    #     c = _Color(c)
    #     return Color(self.red / c.red, self.green / c.green, self.blue / c.blue)

    # def __divmod__(self, c):
    #     c = _Color(c)
    #     dr, mr = divmod(self.red, c.red)
    #     dg, mg = divmod(self.green, c.green)
    #     db, mb = divmod(self.blue, c.blue)
    #     return Color(dr, dg, db), Color(mr, mg, mb)

    def invert(self):
        """Convert to complementary colors."""
        invertColor(self.colors)

    def __len__(self):
        return self.colors.size()

    # def __mod__(self, c):
    #     c = _Color(c)
    #     return Color(self.red % c.red, self.green % c.green, self.blue % c.blue)

    # def __mul__(self, c):
    #     c = _Color(c)
    #     return Color(self.red * c.red, self.green * c.green, self.blue * c.blue)

    def negate(self):
        negateColor(self.colors)

    # def __pow__(self, c, mod):
    #     c = _Color(c)
    #     if mod is None:
    #         return Color(self.red ** c.red,
    #                      self.green ** c.green,
    #                      self.blue ** c.blue)

    #     m = _Color(mod)
    #     return Color(pow(self.red, c.red, m.red),
    #                  pow(self.green, c.green, m.green),
    #                  pow(self.blue, c.blue, m.blue))

    # def __radd__(self, c):
    #     c = _Color(c)
    #     return Color(self.red + c.red, self.green + c.green, self.blue + c.blue)

    # def __repr__(self):
    #     cl = self.__class__
    #     return '%s.%s(%s)' % (cl.__module__, cl.__name__, str(self))

    # def __rdiv__(self, c):
    #     c = _Color(c)
    #     return Color(c.red / self.red, c.green / self.green, c.blue / self.blue)

    # def __rdivmod__(self, c):
    #     c = _Color(c)
    #     dr, mr = divmod(c.red, self.red)
    #     dg, mg = divmod(c.green, self.green)
    #     db, mb = divmod(c.blue, self.blue)
    #     return Color(dr, dg, db), Color(mr, mg, mb)

    def __richcmp__(_ColorList self, _ColorList other, int rcmp):
        return cmpToRichcmp(compareContainers(self.colors, other.colors), rcmp)

    # def __rmod__(self, c):
    #     c = _Color(c)
    #     return Color(c.red % self.red, c.green % self.green, c.blue % self.blue)

    # def __rmul__(self, c):
    #     c = _Color(c)
    #     return Color(c.red * self.red, c.green * self.green, c.blue * self.blue)

    # def __rpow__(self, c, mod):
    #     c = _Color(c)
    #     if mod is None:
    #         return Color(c.red ** self.red,
    #                      c.green ** self.green,
    #                      c.blue ** self.blue)

    #     m = _Color(mod)
    #     return Color(pow(c.red, self.red, m.red),
    #                  pow(c.green, self.green, m.green),
    #                  pow(c.blue, self.blue, m.blue))

    # def __rsub__(self, c):
    #     c = _Color(c)
    #     return Color(c.red - self.red, c.green - self.green, c.blue - self.blue)

    def __str__(self):
        return toString(self.colors).decode('ascii')

    # def __sub__(self, c):
    #     c = _Color(c)
    #     return Color(self.red - c.red, self.green - c.green, self.blue - c.blue)


globals()['ColorList'] = _ColorList
