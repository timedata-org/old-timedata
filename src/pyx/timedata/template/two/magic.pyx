### comment

"""A magic method with two arguments that returns a class."""

### declare
    void magic_$name($class_cpp&, $class_cpp&)

### define
    def __${name}__($class_py self, $class_py x):
        cdef $class_py result = $class_py()
        result.cdata = self.cdata
        magic_$name(x.cdata, result.cdata)
        return result

    def __i${name}__($class_py self, $class_py x):
        magic_$name(x.cdata, self.cdata)
        return self
