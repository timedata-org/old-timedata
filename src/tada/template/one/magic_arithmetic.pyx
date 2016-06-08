### comment
"""These are "magic" arithmetic functions which suffer from the same class isues
   as the magic_list functions do."""

### declare
    $class_cpp magic_$name($class_cpp&, $class_cpp&)

### define
    def __${name}__(object x, object y):
        cdef $class_py result = $class_py()
        result.cdata = magic_$name(
            (<$class_py> x if isinstance(x, $class_py) else $class_py(x)).cdata,
            (<$class_py> y if isinstance(x, $class_py) else $class_py(y)).cdata)
        return result
