### comment
"""This is template code common to both Samples and Lists."""

### declare
import cython
from numbers import Number

cdef extern from "<$include_file>" namespace "$namespace":
    string toString(C$classname&)

### define

cdef class $classname:
    """$class_documentation"""
    cdef C$classname cdata

    START = $start
    RANGE = $range
    MODEL_NAME = '$model'

    cpdef $classname copy($classname self):
        """Return a shallow copy of self."""
        cdef $classname s = $classname()
        s.cdata = self.cdata
        return s

    def __repr__($classname self):
        return '$classname(%s)' % str(self)

    def __str__($classname self):
        return toString(self.cdata).decode('ascii')
