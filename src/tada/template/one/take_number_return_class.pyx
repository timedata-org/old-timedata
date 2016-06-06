### declare
    {class_cpp} {name}({class_py}&, {number_type})

### define
    cpdef {name}({class_py} self, {number_type} x):
        """{documentation}"""
        cdef {class_py} result = {class_py}()
        result.cdata = {name}(self.cdata, x})
        return result
