### declare
    $class_cpp magic_$name($class_cpp&, $class_cpp&)

### define
    def __${name}__(object x, object y):
        cdef $class_py result = $class_py()
        cdef $class_py a = <$class_py> x if isinstance(x, $class_py) else $class_py(x)
        cdef $class_py b = <$class_py> y if isinstance(y, $class_py) else $class_py(y)
        result.cdata = magic_$name(a.cdata, b.cdata);
        return result
