### define property
    @property
    def {propname)(self):
        return self.{member}[{index}]

### declare zero_argument
    {class_cpp} {function_cpp}({class_py}&)

### define zero_argument
    {define} {function_py}({class_py} self):
        """{documentation}"""
        cdef {class_py} s = {class_py}()
        s.{member} = {function_cpp}(self.{member})
        return

### declare one_argument
    {return_type} {function_cpp}({class_py}&, {class_py}&)

### define one_argument
    {define} {function_py}({class_py} self, object x):
        """{documentation}"""
        cdef {class_py} s
        if isinstance(x, {class_py}):
            s = <{class_py}> x
        else:
            s = {class_py}(x)
        return {function_cpp}(self.{member}, s.{member})

### declare one_argument_return_sample
    {class_cpp} {function_cpp}({class_py}&, {class_py}&)

### define one_argument_return_sample
    {define} {function_py}({class_py} self, object x):
        """{documentation}"""
        cdef {class_py} s, result = {class_py}()
        if isinstance(x, {class_py}):
            s = <{class_py}> x
        else:
            s = {class_py}(x)
        result.{member} = {function_cpp}(self.{member}, s.{member})
        return result

### declare magic_method
    {class_cpp} {function_cpp}({class_py}&, {class_py}&)

### define magic_method
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

### declare static_strings
    vector[string] {function_cpp}()

### define static_strings
    @staticmethod
    def {function_py}():
        """{documentation}"""
        cdef vector[string] names
        result = []
        names = {function_cpp}()
        for i in names:
            result.append(i.decode('ascii'))
        return result

### declare static_maker
    {class_cpp} {function_cpp}({param_type})

### define static_maker
    @staticmethod
    def {function_py}({param_type} x):
        """{documentation}"""
        cdef {class_py} result = {class_py}()
        result.{member} = {function_cpp)(x)
        return result
