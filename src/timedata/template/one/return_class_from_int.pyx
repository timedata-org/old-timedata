### declare
    $class_cpp $name($class_cpp&, int)

### define
    cpdef $class_py $name($class_py self, int index):
        """$documentation"""
        cdef $class_py result = $class_py()
        result.cdata = $name(self.cdata, index)
        return result
