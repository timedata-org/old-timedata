### declare
    C$classname magic_$name(C$classname&)

### define
    def __${name}__($classname self):
        """Python magic method __${name}__"""
        cdef $classname s = $mutableclass()
        s.cdata = magic_$name(self.cdata)
        return s

    def $name($classname self):
        """$documentation"""
        cdef $classname s = $mutableclass()
        s.cdata = magic_$name(self.cdata)
        return s
