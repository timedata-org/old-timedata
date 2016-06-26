### declare
    C$classname magic_$name(C$classname&)

### define
    def  __${name}__($classname self):
        cdef $classname s = $classname()
        s.cdata = magic_$name(self.cdata)
        return s
