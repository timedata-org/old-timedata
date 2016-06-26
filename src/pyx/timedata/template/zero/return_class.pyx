### declare
    C$classname $name(C$classname&)

### define
    cpdef $classname $name($classname self):
        """$documentation"""
        cdef $classname s = $classname()
        s.cdata = $name(self.cdata)
        return s
