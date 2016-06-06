### comment
"""This template represents the arithmetic magic operators.

   Cython, like all other Python extensions, handles magic operators differently
   than pure Python classes do - and in a rather surprising manner.

   For each operator, instead of two functions, like `__add__` and `__radd__`,
   there is just one:

       def __add__(self, other):

   and this gets triggered if *either* self *or* other is an instance of this
   class!

   The "surprise" is when you find out that "self" is not actually a member of
   the class you're working in.
"""

### declare
    {class_cpp} {function}({number_type}&, {class_cpp}&)
    {class_cpp} {function}({class_cpp}&, {number_type}&)

### define
    def __{function}__(object self, object other):
        """{documentation}"""
        cdef {class_py} result = {class_py}()

        if isinstance(self, {class_py}):
            result.cdata = {function}((<{class_py}> self).cdata, other)
        else:
            result.cdata = {function}(self, (<{class_py}> other).cdata)

        return result
