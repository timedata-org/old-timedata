include "_render3.pyx"

cdef extern from "<tdsp/signal/render3.h>" namespace "tdsp":
    void renderColorVector(Render3&, ColorVector&, size_t, char*);


cdef class _Render3Impl(_Render3):
    def byte_size(self):
        return 3 * self.size

    def render(self, ColorList cl, size_t pos, bytearray buffer):
        renderColorVector(self._instance, cl.colors, pos,
                          buffer + self.offset)
