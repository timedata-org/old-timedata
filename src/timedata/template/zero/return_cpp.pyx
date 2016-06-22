### comment
"""A method that returns the value of a C++ function directly."""

### declare
    $return_type $name($class_cpp&)

### define
    cpdef $return_type $name($class_py self):
        """$documentation"""
        return $name(self.cdata)
