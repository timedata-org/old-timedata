cdef extern from "<tdsp/color/renderer.h>" namespace "tdsp":
    struct Render3:
        float min, max, brightness, gamma
        uint permutation
        char* buffer
        size_t offset, size

        void render(ColorList&)


cdef class Renderer3:
    cdef Render3 _render

    PERMUTATIONS = 'rgb', 'rbg', 'grb', 'gbr', 'brg', 'bgr'

    def __cinit__(self, object driver):
        self._render.size = driver.size
        self.byte_size = 3 * driver.size
        self._render.offset = len(driver.header)

    def render(self, _ColorList cl):
        self._render.render(cl.colors)

    property message:
        def __set__(self, bytearray x):
            self._render.buffer = x
            self._render.buffer += self._offset

    property min:
        def __get__(self):           return self._render.min
        def __set__(self, float x):  self._render.min = x

    property max:
        def __get__(self):           return self._render.max
        def __set__(self, float x):  self._render.max = x

    property brightness:
        def __get__(self):           return self._render.brightness
        def __set__(self, float x):  self._render.brightness = x

    property gamma:
        def __get__(self):           return self._render.gamma
        def __set__(self, float x):  self._render.gamma = x

    property permutation:
        def __get__(self):
            return self.PERMUTATIONS[self._render.permutation]

        def __set__(self, object p):
            try:
                p = self.PERMS.index(p)
            except ValueError:
                pass
            self._render.permutation = p