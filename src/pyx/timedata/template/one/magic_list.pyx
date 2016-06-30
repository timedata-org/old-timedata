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
    C$classname magic_$name($number_type&, C$classname&)
    C$classname magic_$name(C$classname&, $number_type&)

### define
    def __${name}__(object self, object other):
        """$documentation"""
        cdef $classname result = $classname()

        if isinstance(self, $classname):
            result.cdata = magic_$name((<$classname> self).cdata, other)
        else:
            result.cdata = magic_$name(self, (<$classname> other).cdata)

        return result
