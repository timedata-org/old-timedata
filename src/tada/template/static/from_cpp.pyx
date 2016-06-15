### declare
    void $name($argument_type, $class_cpp&)

### define
    @staticmethod
    def $name($argument_type arg):
        """{documentation}"""
        cdef $class_py result = $class_py()
        $name(arg, result.cdata)
        return result
