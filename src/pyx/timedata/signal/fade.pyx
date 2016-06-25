include "build/genfiles/timedata/signal/fade.pyx"

cdef extern from "<timedata/signal/fade.h>" namespace "timedata":
    void fadeOver(float fader, Fade& fade, ColorVector& in1, ColorVector& in2,
                  ColorVector& out)


cdef class _FadeImpl(_Fade):
    def __call__(self, float fader, ColorList in1, ColorList in2,
                 ColorList out):
        fadeOver(fader, self._instance, in1.colors, in2.colors, out.colors)
