### declare
    $class_cpp $name($class_cpp&)

### define
    cpdef $class_py $name($class_py self):
        """$documentation"""
        cdef $class_py s = $class_py()
        s.cdata = $name(self.cdata)
        return s
