### comment

"""A magic method with two or three arguments that returns a class (in practice,
   just __pow__)."""

### declare
    C$classname magic_$name(C$classname&, C$classname&)
    C$classname magic_$name(C$classname&, C$classname&, C$classname&)

### define
    def __${name}__(object a, object b, object mod):
        """The Python magic method __${name}__."""
        cdef $classname z, result = $classname()

        cdef $classname x = a if isinstance(a, $classname) else $classname(a)
        cdef $classname y = b if isinstance(b, $classname) else $classname(b)

        if mod is None:
            result.cdata = magic_$name(x.cdata, y.cdata)
        else:
            z = mod if isinstance(mod, $classname) else $classname(mod)
            result.cdata = magic_$name(x.cdata, y.cdata, z.cdata)
        return result
