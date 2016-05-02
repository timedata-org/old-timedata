from libcpp.string cimport string

cdef extern from "<tdsp/color/names.h>" namespace "tdsp":
    cdef cppclass RGB:
        pass

    cdef cppclass Frame[T]:
        float& at(int)

    Frame[RGB] toColor(string)
    string colorToString(float r, float g, float b)


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

    def __getitem__(self, int key):
        if key == 0:
            return self.red
        if key == 1:
            return self.green
        if key == 2:
            return self.blue
        raise IndexError('Color index out of range')

    def __len__(self):
        return 3

    def __str__(self):
        return colorToString(self.red, self.green, self.blue)

    def __repr__(self):
        cl = self.__class__
        return '%s.%s(%s)' % (cl.__module__, cl.__name__, str(self))

    @staticmethod
    def from_string(string s):
        cdef Frame[RGB] frame
        # exceptions!
        frame = toColor(s)
        return Color(frame.at(0), frame.at(1), frame.at(2))
