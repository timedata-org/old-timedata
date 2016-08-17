### comment
'This is for `reverse`, a Python method that behaves a little differently'

### declare
    void math_$name(C$classname&, C$classname&)

### define
    cpdef $classname $name($classname self):
        """$documentation that mutates self."""
        math_$name(self.cdata, self.cdata)
        return self

    cpdef $classname ${name}_to($classname self, $classname out):
        """$documentation that writes to another $classname."""
        math_$name(self.cdata, out.cdata)
        return out
