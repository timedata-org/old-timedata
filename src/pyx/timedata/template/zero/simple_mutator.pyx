### declare
    void math_$name(C$classname&)

### define
    cpdef $classname $name($classname self):
        """$documentation."""
        math_$name(self.cdata)
        return self
