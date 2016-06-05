### declare
    {class_cpp} {function_cpp}({class_py}&, {class_py}&)

### define
    def {function_py}(self, object x):
        """{documentation}"""
        cdef {class_py} a, b, result = {class_py}()
        # Remember that this method will be triggered if either `self` or `x`
        # are instances of {class_py}, so we need to check the type of both.
        if isinstance(self, {class_py}):
            a = <{class_py}> self
        else:
            a = {class_py}(self)
        if isinstance(x, {class_py}):
            b = <{class_py}> x
        else:
            b = {class_py}(x)
        result.{member} = {function_cpp}(a.{member}, b.{member})
        return result
