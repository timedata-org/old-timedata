### comment

"""A magic method with two arguments that returns a class."""

### declare
    void magic_$name(C$classname&, C$classname&)

### define
    def __${name}__($classname self, $classname x):
        cdef $classname result = $classname()
        result.cdata = self.cdata
        magic_$name(x.cdata, result.cdata)
        return result

    def __i${name}__($classname self, $classname x):
        magic_$name(x.cdata, self.cdata)
        return self
