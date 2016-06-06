### comment

"""These are zero-operator "magic" arithmetic operators that have a
   corresponding mutator of the same name."""

### declare
    {class_cpp} {function}({class_py}&)

### define
    {define} __{function}__({class_py} self):
        """{documentation}"""
        cdef {class_py} s = {class_py}()
        s.cdata = {function}(self.cdata)
        return s

    {define} {function}({class_py} self):
        """{documentation}"""
        self.cdata = {function}(self.cdata)
        return self
