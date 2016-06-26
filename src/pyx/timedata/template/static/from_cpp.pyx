### declare
    void $name($argument_type, C$classname&)

### define
    @staticmethod
    def $name($argument_type arg):
        """{documentation}"""
        cdef $classname result = $classname()
        $name(arg, result.cdata)
        return result
