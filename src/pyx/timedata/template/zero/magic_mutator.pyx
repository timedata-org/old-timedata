### comment

"""These are zero-argument "magic" arithmetic operators that have a
   corresponding mutator of the same name."""

### declare
    C$classname magic_$name(C$classname&)

### define
    def __${name}__($classname self):
        cdef $classname s = $classname()
        s.cdata = magic_$name(self.cdata)
        return s

    cpdef $classname $name($classname self):
        """Mutating version of __${name}__ that changes self."""
        self.cdata = magic_$name(self.cdata)
        return self
