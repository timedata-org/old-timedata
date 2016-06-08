### declare
    $number_type $name($class_cpp&, $class_cpp&)

### define
    cpdef $number_type $name($class_py self, object x):
        """$documentation"""
        cdef $class_py s = x if isinstance(x, $class_py) else $class_py(x)
        return $name(self.cdata, s.cdata)
