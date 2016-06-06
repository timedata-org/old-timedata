### comment
"""These are "magic" arithmetic functions which suffer from the same class isues
   as the magic_list functions do."""

### declare
    {class_cpp} {function}({class_cpp}&, {class_cpp}&)

### define
    def __{function}__(object self, object other):
        """{documentation}"""
        cdef {class_py} s, o
        cdef {class_py} result = {class_py}()

        if isinstance(self, {class_py}):
            s = self
        else:
            s = {class_py}(self)

        if isinstance(other, {class_py}):
            o = other
        else:
            o = {class_py}(other)

        result.cdata = {function}(s.cdata, o.cdata)
        return result
