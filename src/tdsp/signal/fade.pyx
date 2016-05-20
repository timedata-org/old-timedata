include "_fade.pyx"

cdef extern from "<tdsp/signal/fade.h>" namespace "tdsp":
    void fadeOver(float fader, Fade& fade, ColorVector& in1, ColorVector& in2,
                  ColorVector& out)


cdef class _FadeImpl(_Fade):
    def __call__(self, float fader, _ColorList in1, _ColorList in2,
                 _ColorList out):
        fadeOver(fader, self._instance, in1.colors, in2.colors, out.colors)
