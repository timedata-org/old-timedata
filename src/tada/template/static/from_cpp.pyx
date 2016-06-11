### declare
    $class_cpp $name($argument_type)

### define
    @staticmethod
    def $name($argument_type arg):
        """{documentation}"""
        cdef $class_py x = $class_py()
        x.cdata = $name(arg)
        return x
