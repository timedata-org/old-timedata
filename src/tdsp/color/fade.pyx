include "_fade.pyx"

cdef extern from "<tdsp/color/fade.h>" namespace "tdsp":
    void applyExtend(Fade& fade, float fader,
                     ColorList& in1, ColorList& in2, ColorList& out)


cdef class _FadeImpl(_Fade):
    def apply(self, float fader, _ColorList in1, _ColorList in2, _ColorList o):
        applyExtend(self._fade, fader, in1.colors, in2.colors, o.colors)
