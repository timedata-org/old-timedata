### declare
    $number_type $name(C$classname&, C$classname&)

### define
    cpdef $number_type $name($classname self, object x):
        """$documentation

           Arguments:
               x: a $classname or something that can be converted into one.
        """
        cdef $classname s = x if isinstance(x, $classname) else $classname(x)
        return $name(self.cdata, s.cdata)
