from numbers import Number

cdef class OperatorTest:
    cdef ColorList colors

    cdef _run_into(self, float x, Binary op, Side side=LEFT):
        """An operation that mutates this ColorList."""
        runInto(op, side, <float> x, self.colors)
        return self

    def operator_add(self, float x):
        """An operation that mutates this ColorList."""
        self._run_into(x, ADD)

    def operator_pow(self, float x):
        """An operation that mutates this ColorList."""
        self._run_into(x, POW)

    def class_add(self, float x):
        addInto(<float> x, self.colors)
        return self

    def class_pow(self, float x):
        addInto(<float> x, self.colors)
        return self

    def __str__(self):
        return toString(self.colors, (<_Color> self._color_maker())._base()
                        ).decode('ascii')

    def resize(self, size_t size):
        """Set the size of the ColorList, filling with black if needed."""
        self.colors.resize(size)
