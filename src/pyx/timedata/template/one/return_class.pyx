### declare
    $class_cpp $name($class_cpp&, $class_cpp&)

### define
    cpdef $name($class_py self, object x):
        """$documentation"""
        cdef $class_py s = x if isinstance(x, $class_py) else $class_py(x)
        cdef $class_py result = $class_py()
        result.cdata = $name(self.cdata, s.cdata)
        return result
