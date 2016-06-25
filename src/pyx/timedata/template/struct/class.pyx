### define
cdef extern from "<$header_file>" namespace "$namespace":
$struct_definition

cdef class _$classname(_Wrapper):
    cdef $classname $member_name;
$enum_pyx
    def __cinit__(self):
        clearStruct(self.$member_name)

    def clear(self):
        clearStruct(self.$member_name)

    def __str__(self):
        return "($str_format)" % (
            $variable_names)

$property_list
