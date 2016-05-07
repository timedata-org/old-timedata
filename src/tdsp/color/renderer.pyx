cdef extern from "<tdsp/color/renderer.h>" namespace "tdsp":
    struct Render3:
        float begin, end, brightness, gamma
        uint perm

cdef class Renderer3:
    cdef Render3 render
    cdef uint size, offset
    cdef bytearray _message

    def __cinit__(self, driver):
        self.size = driver.size
        self.offset = len(driver.header)
        self.byte_size = 3 * self.size

    property message:
        def __get__(self):              return self._message
        def __set__(self, bytearray x): self._message = x

    property begin:
        def __get__(self):              return self.render.begin
        def __set__(self, float x):     self.self.render.begin = x

    property end:
        def __get__(self):              return self.render.end
        def __set__(self, float x):     self.self.render.end = x

    property brightness:
        def __get__(self):              return self.render.brightness
        def __set__(self, float x):     self.self.render.brightness = x

    property gamma:
        def __get__(self):              return self.render.gamma
        def __set__(self, float x):     self.self.render.gamma = x

    def render(self):
        pass
