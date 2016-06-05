### declare
    {class_cpp} {function_cpp}({param_type})

### define
    @staticmethod
    def {function_py}({param_type} x):
        """{documentation}"""
        cdef {class_py} result = {class_py}()
        result.{member} = {function_cpp)(x)
        return result

    def __init__(self, *args):
        """There are various different ways to construct a {class_py}.

        * The empty constructor {class_py}() set all components to zero.
        * {class_py}s can be constructed from string names.
        * Constructing from a single number results in a sample with all
          components of that value.
        * Constructing from any sort of tuple of the right size works
          as expected.
        """
        if len(args) == 1:
            a = args[0]
            if isinstance(a, Number):
                self.{member}.fill(a)
                return
            if isinstance(a, str):
                if {from_string}(a, self.{member}):
                    return
                raise ValueError("Can't understand sample string %s" % args)
            try:
                args = tuple(a)
            except:
                raise ValueError("Can't understand sample tuple %s" % args)

        if not args:
            self.{member}.fill(0)
        elif len(args) != {size}:
            raise ValueError("Wrong args length %s" % args)
        else:
            for i, a in enumerate(args):
                self.{member}[i] = a
