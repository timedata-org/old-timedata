### comment
"""A method that returns the value of a C++ function directly."""

### declare
    $return_type $name(C$classname&)

### define
    cpdef $return_type $name($classname self):
        """$documentation"""
        return $name(self.cdata)
