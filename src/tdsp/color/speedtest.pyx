from numbers import Number

cdef class OperatorTest:
    cdef ColorList colors

    cdef _ColorList _make(self, object value=None):
        return _ColorList(value, color_maker=self._color_maker,
                          class_name=self.class_name)

    cdef _ColorList _toColorList(self, object value):
        if isinstance(value, _ColorList):
            return <_ColorList> value
        else:
            return self._make(value)

    cdef _run_into(self, object x, Binary op, Side side=LEFT):
        """An operation that mutates this ColorList."""
        if isinstance(x, Number):
            runInto(op, side, <float> x, self.colors)
        else:
            runInto(op, side, self._toColorList(x).colors, self.colors)
        return self

    def operator_add(self, object x):
        """An operation that mutates this ColorList."""
        self._run_into(x, ADD)

    def operator_pow(self, object x):
        """An operation that mutates this ColorList."""
        self._run_into(x, POW)

    def class_add(self, object x):
        if isinstance(x, Number):
            addInto(<float> x, self.colors)
        else:
            addInto(self._toColorList(x).colors, self.colors)
        return self

    def class_pow(self, object x):
        if isinstance(x, Number):
            addInto(<float> x, self.colors)
        else:
            addInto(self._toColorList(x).colors, self.colors)
        return self

    def __str__(self):
        return toString(self.colors, (<_Color> self._color_maker())._base()
                        ).decode('ascii')

    def resize(self, size_t size):
        """Set the size of the ColorList, filling with black if needed."""
        self.colors.resize(size)
