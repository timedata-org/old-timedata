### declare
cdef extern from "<timedata/color/cython_inl.h>" namespace "timedata::color":
    cdef cppclass C$classname:
        pass
    void $name($argument_type, C$classname&)

### define
    @staticmethod
    def $name($argument_type arg):
        """$documentation"""
        cdef $classname result = $classname()
        $name(arg, result.cdata)
        return result
