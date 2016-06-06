### declare
    {class_cpp} {function_cpp}({class_py}&)

### define
    {define} {function_py}({class_py} self):
        """{documentation}"""
        cdef {class_py} s = {class_py}()
        s.cdata = {function_cpp}(self.cdata)
        return s
