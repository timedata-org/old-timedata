include "_render3.pyx"

cdef extern from "<tdsp/signal/render3.h>" namespace "tdsp":
    void renderColorList(Render3&, ColorList&, char*);


cdef class _Render3Impl(_Render3):
    cdef char* buffer

    def byte_size(self):
        return 3 * self.size

    property message:
        def __get__(self):
            return bytearray(self.buffer)
        def __set__(self, bytearray x):
            self.buffer = x

    def __call__(self, _ColorList cl):
        renderColorList(self._instance, cl.colors, self.buffer + self.offset)
