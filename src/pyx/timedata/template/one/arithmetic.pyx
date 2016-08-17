### declare
    void math_$name(C$classname&, $number_type, C$classname&)
    void math_$name(C$classname&, C$sampleclass&, C$classname&)
    void math_$name(C$classname&, C$classname&, C$classname&)

### define
    cpdef $classname $name($classname self, object c):
        """$documentation into this $classname."""
        return self.${name}_into(c)

    cpdef $classname ${name}_into($classname self, object c):
        """$documentation into this $classname."""
        if isinstance(c, Number):
            math_$name(self.cdata, <$number_type> c, self.cdata)
        elif isinstance(c, $sampleclass):
            math_$name(self.cdata, (<$sampleclass> c).cdata, self.cdata)
        else:
            math_$name(self.cdata, (<$classname> c).cdata, self.cdata)
        return self

    cpdef $classname ${name}_to($classname self, object c, $classname x):
        """$documentation onto another $classname."""
        if isinstance(c, Number):
            math_$name(self.cdata, <$number_type> c, x.cdata)
        elif isinstance(c, $sampleclass):
            math_$name(self.cdata, (<$sampleclass> c).cdata, x.cdata)
        else:
            math_$name(self.cdata, (<$classname> c).cdata, x.cdata)
        return x
