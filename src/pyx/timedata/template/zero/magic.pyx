### declare
    C$classname magic_$name(C$classname&)

### define
    def $name($classname self):
        """$documentation"""
        cdef $classname s = $mutableclass()
        s.cdata = magic_$name(self.cdata)
        return s
