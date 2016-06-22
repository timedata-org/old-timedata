### declare
    void math_$name($value_type, $class_cpp&)
    void math_$name($class_cpp&, $class_cpp&)

### define
    cpdef $class_py $name($class_py self, object c):
        """ into colors from either a number or a ColorList."""
        if isinstance(c, Number):
            math_$name(<$value_type> c, self.cdata)
        else:
            math_$name((<$class_py> c).cdata, self.cdata)
        return self
