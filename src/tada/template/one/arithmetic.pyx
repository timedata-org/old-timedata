### declare
    void $name($value_type, $class_cpp&)
    void $name($class_cpp&, $class_cpp&)

### define
    cpdef $class_py $name($class_py self, object c):
        """ into colors from either a number or a ColorList."""
        if isinstance(c, Number):
            $name(c, self.cdata)
        else:
            $name((<$class_py> c).cdata, self.cdata)
        return self
