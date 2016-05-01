cdef extern from "<tdsp/color/names.h>" namespace "tdsp":
    pass

cdef class Color:
    cdef float red
    cdef float green
    cdef float blue

    def __cinit__(self, float red=0, float green=0, float blue=0):
        self.red = red
        self.green = green
        self.blue = blue

    @property
    def red(self):
        return self.red

    @property
    def green(self):
        return self.green

    @property
    def blue(self):
        return self.blue

    def __len__(self):
        return 3

    def __getitem__(self, int key):
        if key == 0:
            return self.red
        if key == 1:
            return self.green
        if key == 2:
            return self.blue
        raise IndexError('Color index out of range')
