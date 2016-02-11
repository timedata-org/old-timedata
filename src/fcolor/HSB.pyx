cdef extern from "fcolor/HSB.h" namespace "fcolor::HSB":
    float interpolateHue(float x, float y, float r)
    FColor hsbFromRgb(FColor color)

def interpolate_hue(float x, float y, float r):
    return interpolateHue(x, y, r)
