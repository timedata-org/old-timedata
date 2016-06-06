### comment
"""A method that returns a C++ function directly."""

### declare
    {return_type} {function_cpp}({class_cpp}&)

### define
    cpdef {return_type} {function_py}({class_py} self):
        """{documentation}"""
        return {function_cpp}(self.cdata)
