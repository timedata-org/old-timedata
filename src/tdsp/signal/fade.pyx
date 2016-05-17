include "_fade.pyx"

cdef extern from "<tdsp/signal/fade.h>" namespace "tdsp":
    void fadeOver(float fader, Fade& fade, ColorList& in1, ColorList& in2,
                  ColorList& out)


cdef class _FadeImpl(_Fade):
    def __call__(self, float fader, _ColorList in1, _ColorList in2,
                 _ColorList out):
        fadeOver(fader, self._instance, in1.colors, in2.colors, out.colors)
