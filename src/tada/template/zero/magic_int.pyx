### comment
"""A magic method that returns a C++ int directly."""

### declare
    int {function}({class_cpp}&)

### define
    def __{function}__({class_py} self):
        """{documentation}"""
        return {function}(self.cdata)
