from numbers import Number

cdef class OperatorTest:
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

    def operator_add(self, float x):
        """An operation that mutates this ColorList."""
        runInto(ADD, LEFT, x, self.colors)

    def class_add(self, float x):
        addInto(x, self.colors)

    def __str__(self):
        return toString(self.colors, (<_Color> self._color_maker())._base()
                        ).decode('ascii')

    def resize(self, size_t size):
        """Set the size of the ColorList, filling with black if needed."""
        self.colors.resize(size)
