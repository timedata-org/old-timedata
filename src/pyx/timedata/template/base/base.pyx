### comment
"""This is template code common to both Samples and Lists."""

### declare
import cython
from numbers import Number

### define

cdef class $classname:
    """$class_documentation"""
    cdef C$classname cdata

    START = $start
    MODEL_NAME = '$model'

    def __repr__($classname self):
        return '$classname(%s)' % str(self)

    def __str__($classname self):
        return toString(self.cdata).decode('ascii')

    def __sizeof__($classname self):
        return getSizeof(self.cdata)
