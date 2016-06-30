### declare
    void math_$name($number_type, C$classname&)
    void math_$name(C$sampleclass&, C$classname&)
    void math_$name(C$classname&, C$classname&)

### define
    cpdef $classname $name($classname self, object c):
        """ into colors from either a number or a ColorList."""
        if isinstance(c, Number):
            math_$name(<$number_type> c, self.cdata)
        elif isinstance(c, $sampleclass):
            math_$name((<$sampleclass> c).cdata, self.cdata)
        else:
            math_$name((<$classname> c).cdata, self.cdata)
        return self
