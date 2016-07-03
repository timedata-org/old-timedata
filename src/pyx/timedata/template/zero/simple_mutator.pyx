### declare
    void math_$name(C$classname&)

### define
    cpdef $classname $name($classname self):
        """Mutating version of __${name}__ that changes self."""
        math_$name(self.cdata)
        return self
