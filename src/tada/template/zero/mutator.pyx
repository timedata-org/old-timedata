### declare
    void math_$name($class_cpp&)

### define
    cpdef $class_py $name($class_py self):
        """Mutating version of __${name}__ that changes self."""
        math_$name(self.cdata)
        return self
