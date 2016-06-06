### declare
    {class_cpp} {function}({class_py}&, {number_type})

### define
    cpdef {function}({class_py} self, {number_type} x):
        """{documentation}"""
        cdef {class_py} result = {class_py}()
        result.cdata = {function}(self.cdata, x})
        return result
