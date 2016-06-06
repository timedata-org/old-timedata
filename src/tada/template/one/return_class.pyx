### declare
    {class_cpp} {function}({class_py}&, {class_py}&)

### define
    {define} {function}({class_py} self, object x):
        """{documentation}"""
        cdef {class_py} s, result = {class_py}()
        if isinstance(x, {class_py}):
            s = <{class_py}> x
        else:
            s = {class_py}(x)
        result.cdata = {function}(self.cdata, s.cdata)
        return result
