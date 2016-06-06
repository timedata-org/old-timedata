### declare
    {class_cpp} {name_cpp}({class_py}&)

### define
    cpdef {class_py} {name_py}({class_py} self):
        """{documentation}"""
        cdef {class_py} s = {class_py}()
        s.cdata = {name_cpp}(self.cdata)
        return s
