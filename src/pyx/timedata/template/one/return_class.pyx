### declare
    C$classname $name(C$classname&, C$classname&)

### define
    cpdef $name($classname self, object x):
        """$documentation

           Arguments:
               x: a $classname or something that can be converted into one.
        """
        cdef $classname s = x if isinstance(x, $classname) else $classname(x)
        cdef $mutableclass result = $mutableclass()
        result.cdata = $name(self.cdata, s.cdata)
        return result
