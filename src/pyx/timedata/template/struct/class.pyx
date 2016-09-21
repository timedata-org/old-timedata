### define
cdef extern from "<$header_file>" namespace "$namespace":
$struct_definition

cdef class _$classname(_Wrapper):
    cdef $classname cdata;
$enum_pyx
    def __cinit__(self):
        clearStruct(self.cdata)

    def __str__(self):
        return "($str_format)" % (
            $variable_names)

    def clear(self):
        """Clear the $classname to its initial state."""
        clearStruct(self.cdata)

    cpdef _$classname copy(self):
        cdef _$classname other = _$classname()
        other.cdata = self.cdata
        return other

    def __copy__(self):
      return self.copy()

    def __deepcopy__(self, memodict={}):
        return self.copy()

    def __getstate__(self):
        return $variable_names

    def __setstate__(self, state):
        $variable_names = state

$property_list

locals()['$classname'] = _$classname
