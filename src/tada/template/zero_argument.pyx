### declare
    {class_cpp} {function_cpp}({class_py}&)

### define
    {define} {function_py}({class_py} self):
        """{documentation}"""
        cdef {class_py} s = {class_py}()
        s.{member} = {function_cpp}(self.{member})
        return
