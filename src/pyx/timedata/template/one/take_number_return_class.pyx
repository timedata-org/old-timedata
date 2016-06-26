### declare
    C$classname $name(C$classname&, $value_type)

### define
    cpdef $name($classname self, $value_type x):
        """$documentation"""
        cdef $classname result = $classname()
        result.cdata = $name(self.cdata, x)
        return result
