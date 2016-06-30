### declare
    C$classname $name(C$classname&, $number_type)

### define
    cpdef $name($classname self, $number_type x):
        """$documentation"""
        cdef $classname result = $classname()
        result.cdata = $name(self.cdata, x)
        return result
