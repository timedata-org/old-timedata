### comment

"""These are zero-argument "magic" arithmetic operators that have a
   corresponding mutator of the same name."""

### declare
    $class_cpp magic_$name($class_cpp&)

### define
    def __${name}__($class_py self):
        cdef $class_py s = $class_py()
        s.cdata = $name(self.cdata)
        return s

    cpdef $class_py $name($class_py self):
        """Mutating version of __${name}__ that changes self."""
        self.cdata = magic_$name(self.cdata)
        return self
