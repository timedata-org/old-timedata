### declare
    C$classname magic_$name(C$classname&, C$classname&)

### define
    def $name($classname self, object x):
        """Python magic method __${name}__."""
        cdef $sampleclass a = x if isinstance(x, $sampleclass) else self.__class__(x)

        result = $mutableclass()
        (<$sampleclass> result).cdata = magic_$name(self.cdata, a.cdata);
        return result
