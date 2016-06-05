### declare
    {return_type} {function_cpp}({class_py}&, {class_py}&)

### define
    {define} {function_py}({class_py} self, object x):
        """{documentation}"""
        cdef {class_py} s
        if isinstance(x, {class_py}):
            s = <{class_py}> x
        else:
            s = {class_py}(x)
        return {function_cpp}(self.{member}, s.{member})
