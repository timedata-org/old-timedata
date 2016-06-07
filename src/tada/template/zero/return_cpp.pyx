### comment
"""A method that returns the value of a C++ function directly."""

### declare
    $return_type $name_cpp($class_cpp&)

### define
    cpdef $return_type $name_py($class_py self):
        """$documentation"""
       return $name_cpp(self.cdata)
