### declare
    C$classname $name(C$classname&, C$classname&)

### define
    cpdef $name($classname self, object x):
        """$documentation"""
        cdef $classname s = x if isinstance(x, $classname) else $classname(x)
        cdef $classname result = $classname()
        result.cdata = $name(self.cdata, s.cdata)
        return result
