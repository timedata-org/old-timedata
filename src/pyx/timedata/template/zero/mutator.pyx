### declare
    void math_$name(C$classname&, C$classname&)

### define
    cpdef $classname $name($classname self):
        """Mutating version of __${name}__ that changes self."""
        math_$name(self.cdata, self.cdata)
        return self

    cpdef $classname ${name}_to($classname self, $classname out):
        """Mutating version of __${name}__ that changes self."""
        math_$name(self.cdata, out.cdata)
        return out
