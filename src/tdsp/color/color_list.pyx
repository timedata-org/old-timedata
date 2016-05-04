

cdef class ColorList:
    cdef vector[Color] colors

    def __cinit__(self):
        pass

    # @property
    # def red(self):
    #     return self.red

    # @property
    # def green(self):
    #     return self.green

    # @property
    # def blue(self):
    #     return self.blue

    # @staticmethod
    # def make(x):
    #     if isinstance(x, Color):
    #         return x

    #     cdef Sample[RGB] frame
    #     try:
    #         if isinstance(x, str):
    #             if toColor(x, frame):
    #                 return Color(frame.at(0), frame.at(1), frame.at(2))

    #         try:
    #             len(x)
    #         except:
    #             return Color(x, x, x)
    #         if len(x) == 3:
    #             return Color(*x)
    #         raise ValueError()

    #     except:
    #         raise ValueError("Can't understand color %s" % x)

    # def __getitem__(self, int key):
    #     if key == 0:
    #         return self.red
    #     if key == 1:
    #         return self.green
    #     if key == 2:
    #         return self.blue
    #     raise IndexError('Color index out of range')

    # def __abs__(self):
    #     return Color(abs(self.red), abs(self.green), abs(self.blue))

    # def __add__(self, c):
    #     c = Color.make(c)
    #     return Color(self.red + c.red, self.green + c.green, self.blue + c.blue)

    # def __div__(self, c):
    #     c = Color.make(c)
    #     return Color(self.red / c.red, self.green / c.green, self.blue / c.blue)

    # def __divmod__(self, c):
    #     c = Color.make(c)
    #     dr, mr = divmod(self.red, c.red)
    #     dg, mg = divmod(self.green, c.green)
    #     db, mb = divmod(self.blue, c.blue)
    #     return Color(dr, dg, db), Color(mr, mg, mb)

    # def __invert__(self):
    #     """Return the complementary color."""
    #     return Color(1.0 - self.red, 1.0 - self.green, 1.0 - self.blue)

    # def __len__(self):
    #     return 3

    # def __mod__(self, c):
    #     c = Color.make(c)
    #     return Color(self.red % c.red, self.green % c.green, self.blue % c.blue)

    # def __mul__(self, c):
    #     c = Color.make(c)
    #     return Color(self.red * c.red, self.green * c.green, self.blue * c.blue)

    # def __neg__(self):
    #     return Color(-self.red, -self.green, -self.blue)

    # def __pow__(self, c, mod):
    #     c = Color.make(c)
    #     if mod is None:
    #         return Color(self.red ** c.red,
    #                      self.green ** c.green,
    #                      self.blue ** c.blue)

    #     m = Color.make(mod)
    #     return Color(pow(self.red, c.red, m.red),
    #                  pow(self.green, c.green, m.green),
    #                  pow(self.blue, c.blue, m.blue))

    # def __radd__(self, c):
    #     c = Color.make(c)
    #     return Color(self.red + c.red, self.green + c.green, self.blue + c.blue)

    # def __repr__(self):
    #     cl = self.__class__
    #     return '%s.%s(%s)' % (cl.__module__, cl.__name__, str(self))

    # def __rdiv__(self, c):
    #     c = Color.make(c)
    #     return Color(c.red / self.red, c.green / self.green, c.blue / self.blue)

    # def __rdivmod__(self, c):
    #     c = Color.make(c)
    #     dr, mr = divmod(c.red, self.red)
    #     dg, mg = divmod(c.green, self.green)
    #     db, mb = divmod(c.blue, self.blue)
    #     return Color(dr, dg, db), Color(mr, mg, mb)

    # def __richcmp__(Color self, Color c, int cmp):
    #     return cmpToRichcmp((self.red - c.red) or
    #                         (self.green - c.green) or
    #                         (self.blue - c.blue), cmp)

    # def __rmod__(self, c):
    #     c = Color.make(c)
    #     return Color(c.red % self.red, c.green % self.green, c.blue % self.blue)

    # def __rmul__(self, c):
    #     c = Color.make(c)
    #     return Color(c.red * self.red, c.green * self.green, c.blue * self.blue)

    # def __round__(self, n):
    #     return Color(round(self.red, n),
    #                  round(self.green, n),
    #                  round(self.blue, n))

    # def __rpow__(self, c, mod):
    #     c = Color.make(c)
    #     if mod is None:
    #         return Color(c.red ** self.red,
    #                      c.green ** self.green,
    #                      c.blue ** self.blue)

    #     m = Color.make(mod)
    #     return Color(pow(c.red, self.red, m.red),
    #                  pow(c.green, self.green, m.green),
    #                  pow(c.blue, self.blue, m.blue))

    # def __rsub__(self, c):
    #     c = Color.make(c)
    #     return Color(c.red - self.red, c.green - self.green, c.blue - self.blue)

    # def __str__(self):
    #     return colorToString(self.red, self.green, self.blue).decode('ascii')

    # def __sub__(self, c):
    #     c = Color.make(c)
    #     return Color(self.red - c.red, self.green - c.green, self.blue - c.blue)
