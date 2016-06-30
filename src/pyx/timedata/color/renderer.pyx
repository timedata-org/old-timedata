cdef class Renderer:
    """A renderer is an abstract base for classes that render strips
       (of colors, for the moment)."""
    property colors:
        def __get__(self):
            return self.colors
        def __set__(self, object x):
            self.colors = _make_ColorList

    def __cinit__(self, colors=None):
        self.colors = colors or OldColorList()

    cpdef void render(self):
        # Call this to update self.colors
        pass
