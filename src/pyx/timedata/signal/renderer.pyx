cdef extern from "<timedata/color/renderer_inl.h>" namespace "timedata::color_list":
    cdef cppclass CRenderer:
        CRenderer(Render3&)
        CRenderer()
        void render(float level, CColorListRGB& input, char* output)


cdef class Renderer(_Render3):
    cdef CRenderer renderer
    cdef float level

    def __init__(self, *, level=1.0, **kwds):
        super().__init__(**kwds)
        self.renderer = CRenderer(self.cdata)
        self.level = level

    property level:
        def __get__(self):
            return self.level
        def __set__(self, float x):
            self.level = x

    def render(self, object colors, bytearray output=None):
        cdef ColorListRGB _colors
        if isinstance(colors, ColorListRGB):
            _colors = colors
        else:
            _colors = ColorListRGB(colors)
        output = output or bytearray(3 * _colors.cdata.size())
        self.renderer.render(self.level, _colors.cdata, output)
        return output
