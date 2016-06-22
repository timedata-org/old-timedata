### declare
    $class_cpp $name($class_cpp&, $value_type)

### define
    cpdef $name($class_py self, $value_type x):
        """$documentation"""
        cdef $class_py result = $class_py()
        result.cdata = $name(self.cdata, x)
        return result
