### comment
"""A method with two or three arguments that returns a class (in practice, just
   __pow__)."""

### declare
    $class_cpp $name($class_cpp&, $class_cpp&)
    $class_cpp $name($class_cpp&, $class_cpp&, $class_cpp&)

### define
    def __${name}__(object a, object b, object mod):
        cdef <$class_py> x = a if isinstance(a, $class_py) else $class_py(a)
        cdef <$class_py> y = b if isinstance(b, $class_py) else $class_py(b)
        cdef $class_py z, result = $class_py()

        if m is None:
            result.cdata = $name(x.cdata, y.cdata)
        else:
            z = mod if isinstance(self, $class_py) else $class_py(mod)
            result.cdata = $name(x.cdata, y.cdata, z.cdata)
        return result
