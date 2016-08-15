### declare
    C$classname $name(C$classname&, int)

### define
    cpdef $classname $name($classname self, int index):
        """$documentation"""
        cdef $classname result = $mutableclass()
        result.cdata = $name(self.cdata, index)
        return result
