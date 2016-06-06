### declare
    {class_cpp} {function}({class_py}&)

### define
    {define}  __{function}__({class_py} self):
        """{documentation}"""
        cdef {class_py} s = {class_py}()
        s.cdata = {function}(self.cdata)
        return s
