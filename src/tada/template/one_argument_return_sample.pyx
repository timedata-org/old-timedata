### declare
    {class_cpp} {function_cpp}({class_py}&, {class_py}&)

### define
    {define} {function_py}({class_py} self, object x):
        """{documentation}"""
        cdef {class_py} s, result = {class_py}()
        if isinstance(x, {class_py}):
            s = <{class_py}> x
        else:
            s = {class_py}(x)
        result.{member} = {function_cpp}(self.{member}, s.{member})
        return result
