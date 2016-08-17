### declare
    C$classname magic_$name(C$classname&, C$classname&)

### define
    def __${name}__(object x, object y):
        """Python magic method __${name}__."""
        cdef $sampleclass a = x if isinstance(x, $sampleclass) else y.__class__(x)
        cdef $sampleclass b = y if isinstance(y, $sampleclass) else x.__class__(y)

        result = $mutableclass()
        (<$sampleclass> result).cdata = magic_$name(a.cdata, b.cdata);
        return result

    def $name($classname self, object x):
        """Python magic method __${name}__."""
        cdef $sampleclass a = x if isinstance(x, $sampleclass) else self.__class__(x)

        result = $mutableclass()
        (<$sampleclass> result).cdata = magic_$name(self.cdata, a.cdata);
        return result
