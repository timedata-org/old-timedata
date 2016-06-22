### declare
    $class_cpp magic_$name($class_cpp&)

### define
    def  __${name}__($class_py self):
        cdef $class_py s = $class_py()
        s.cdata = magic_$name(self.cdata)
        return s
