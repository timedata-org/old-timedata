### declare
    C$classname magic_$name(C$classname&, C$classname&)

### define
    def __${name}__(object x, object y):
        """Python magic method __${name}__."""
        cdef $classname a = x if isinstance(x, $classname) else y.__class__(x)
        cdef $classname b = y if isinstance(y, $classname) else x.__class__(y)

        result = $mutableclass()
        (<$classname> result).cdata = magic_$name(a.cdata, b.cdata);
        return result
