cdef extern from "<tdsp/color/renderer.h>" namespace "tdsp":
    struct Render3:
        float begin, end, brightness, gamma
        uint perm



    cdef class Renderer:
cdef struct Render:
