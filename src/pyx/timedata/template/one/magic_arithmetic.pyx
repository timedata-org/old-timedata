### declare
    C$classname magic_$name(C$classname&, C$classname&)

### define
    def __${name}__(object x, object y):
        cdef $classname result = $classname()
        cdef $classname a = <$classname> x if isinstance(x, $classname) else $classname(x)
        cdef $classname b = <$classname> y if isinstance(y, $classname) else $classname(y)
        result.cdata = magic_$name(a.cdata, b.cdata);
        return result
