### comment
"""A method with two or three arguments that returns a class (in practice, just
   __pow__)."""

### declare
    {class_cpp} {function}({class_cpp}&, {class_cpp}&)
    {class_cpp} {function}({class_cpp}&, {class_cpp}&, {class_cpp}&)

### define
    def __{function}__(object a, object b, object m):
        cdef {class_py} x, y, z, result = {class_py}()
        x = <{class_py}>(a) isinstance(self, {class_py}) else {class_py}(a)
        y = <{class_py}>(b) isinstance(self, {class_py}) else {class_py}(b)

        if m is None:
            result.cdata = {function}(x.cdata, y.cdata)
        else:
            z = <{class_py}>(m) isinstance(self, {class_py}) else {class_py}(m)
            result.cdata = {function}(x.cdata, y.cdata, z.cdata)
        return result
