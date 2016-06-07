### declare
    $class_cpp $name($class_py&)

### define
    def  __${name}__($class_py self):
        cdef $class_py s = $class_py()
        s.cdata = $name(self.cdata)
        return s
