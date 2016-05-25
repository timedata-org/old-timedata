include "_render3.pyx"

cdef extern from "<tada/signal/render3.h>" namespace "tada":
    void renderColorVector(
        Render3&, ColorVector&, size_t pos, char*)


cdef class _Render3Impl(_Render3):
    cpdef byte_size(self):
        return 3 * self.size

    cpdef render(self, ColorList cl, size_t pos, bytearray buffer):
        cdef char* buf
        buf = buffer
        buf += self.offset
        renderColorVector(self._instance, cl.colors, pos, buf)
