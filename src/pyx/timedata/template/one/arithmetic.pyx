### declare
    void math_$name($value_type, C$classname&)
    void math_$name(C$classname&, C$classname&)

### define
    cpdef $classname $name($classname self, object c):
        """ into colors from either a number or a ColorList."""
        if isinstance(c, Number):
            math_$name(<$value_type> c, self.cdata)
        else:
            math_$name((<$classname> c).cdata, self.cdata)
        return self
