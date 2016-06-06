### declare
    {class_cpp} {name}({class_py}&, {class_py}&)

### define
    cpdef {name}({class_py} self, object x):
        """{documentation}"""
        cdef {class_py} s, result = {class_py}()
        if isinstance(x, {class_py}):
            s = <{class_py}> x
        else:
            s = {class_py}(x)
        result.cdata = {name}(self.cdata, s.cdata)
        return result
