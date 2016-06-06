### declare
    {class_cpp} {name}({class_py}&)

### define
    def  __{name}__({class_py} self):
        """{documentation}"""
        cdef {class_py} s = {class_py}()
        s.cdata = {name}(self.cdata)
        return s
